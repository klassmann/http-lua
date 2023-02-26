/* http-lua
 * Author: Lucas Klassmann
 * License: Apache 2.0
 * A small webserver written in C and embedded Lua for application development. It works with epoll() for async.
 */
#define _GNU_SOURCE

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/signalfd.h>
#include <unistd.h>
#include <signal.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <arpa/inet.h>

#define HTTP_PORT 8000                  // Port to listen
#define MAX_CONNECTIONS 2048            // Number of connections supported
#define SCRIPT_FILENAME "app/app.lua"
#define SCRIPT_ENTRYPOINT "index"       // script entry point

///////////////////////////// MEMORY HELPERS /////////////////////////////////
static int memory_alloc_count = 0;      // Help to track memory when debugging
static size_t memory_alloc_size = 0;

void *mem_alloc(size_t size) {
    memory_alloc_count++;
    memory_alloc_size += size;
    return malloc(size);
}

void mem_free(void *ptr, size_t size) {
    memory_alloc_count--;
    memory_alloc_size -= size;
    free(ptr);
}

///////////////////////////// TERMINAL FORMATS ////////////////////////////////
#define TERM_GREEN(x) "\x1b[32m" x "\x1b[0m"
#define TERM_CYAN(x) "\x1b[36m" x "\x1b[0m"

///////////////////////////// LOGS  ///////////////////////////////////////////
#define OK          1
#define INFO        2
#define ERROR       3
#define STD_OUT    stdout
#define STD_ERR    stderr
#define LOG(p, stream, msg, ...)                    \
do {                                                \
    char *str;                                      \
    if (p == INFO)                                  \
        str = "INFO";                               \
    else if (p == ERROR)                            \
        str = "ERR";                                \
    else if (p == OK)                               \
        str = "OK";                                 \
    fprintf(stream, "[%s]:" msg "\n",               \
            str, ##__VA_ARGS__);                    \
} while (0)
#define LOG_INFO(msg, ...) LOG(INFO, STD_OUT, TERM_CYAN(msg), __VA_ARGS__)
#define LOG_OK(msg, ...) LOG(OK, STD_OUT, TERM_GREEN(msg), __VA_ARGS__)
#define LOG_ERR(msg, ...) LOG(ERROR, STD_ERR, msg, __VA_ARGS__)
#define panic(msg)                      \
    LOG_ERR("panic: %s", msg);          \
    do {exit(EXIT_FAILURE);} while(0)


///////////////////////// HTTP ///////////////////////////////////////////////
#define HEADER_EXTRA_SIZE 128
#define HEADER_COUNT 512
#define REQUEST_HEADER_SIZE 4096
#define HEADER_KEY_SIZE 1024
#define HEADER_VALUE_SIZE 1024
#define HTTP_PATH_SIZE 1024
#define MIMETYPE_HTML "text/html"

const char *http_response_fmt =
        "HTTP/1.1 %d %s\n"
        "Content-Type: %s; charset=utf-8\n"
        "Date: Sun, 29 Jan 2023 06:26:25 GMT\n"
        "Content-Length: %d\n\n"                // Two line breaks to separate the response header and body
        "%s";

typedef struct KeyValue {
    char key[HEADER_KEY_SIZE];
    char value[HEADER_VALUE_SIZE];
} KeyValue;

KeyValue *keyvalue_new(const char *s) {
    KeyValue *kv = mem_alloc(sizeof(KeyValue));
    char key[HEADER_KEY_SIZE];
    char value[HEADER_VALUE_SIZE];

    memset(&key, 0, sizeof(key));
    memset(&value, 0, sizeof(value));
    memset(kv, 0, sizeof(KeyValue));

    size_t idx = 0;
    short reading_key = 1;
    char prev = 0;
    for (int j = 0; s[j] != '\0'; j++) {
        char c = s[j];

        if (c == '\r' || c == '\n' || (c == ' ' && prev == ':')) {
            prev = c;
            continue;
        }

        if (reading_key == 1 && c == ':') {
            strncpy(kv->key, key, idx);
            idx = 0;
            reading_key = 0;
            prev = c;
            continue;
        }

        if (reading_key == 1) {
            key[idx] = c;
        }

        if (reading_key != 1) {
            value[idx] = c;
        }
        idx++;
        prev = c;
    }
    strncpy(kv->value, value, idx);
    return kv;
}

void keyvalue_free(KeyValue *kv) {
    mem_free(kv, sizeof(KeyValue));
}

typedef struct Request {
    char method[8];
    char path[HTTP_PATH_SIZE];
    uint32_t header_count;
    KeyValue *headers[HEADER_COUNT];
    size_t size;
} Request;

void request_add_header(Request *req, KeyValue *kv) {
    req->headers[req->header_count] = kv;
    req->header_count++;
}

// Read the incoming data and parse them into method, path and headers fields.
Request *request_new(char *http_request) {
    char request_method[8];
    char path[HTTP_PATH_SIZE];
    char protocol[16];
    sscanf(http_request, "%s %s %s", request_method, path, protocol);
    Request *r = mem_alloc(sizeof(Request));

    r->header_count = 0;
    strcpy(r->method, request_method);
    strcpy(r->path, path);

    char *buff = strtok(http_request, "\n");
    buff = strtok(NULL, "\r\n");  // jump first line
    while (buff != NULL) {
        KeyValue *kv = keyvalue_new(buff);
        request_add_header(r, kv);
        buff = strtok(NULL, "\r\n");
    }
    return r;
}

void request_free(Request *r) {
    for (int j = 0; j < r->header_count; j++) {
        KeyValue *p = r->headers[j];
        if (p != NULL) {
            keyvalue_free(p);
        }
    }
    mem_free(r, sizeof(Request));
}

char *http_reason(unsigned int status) {
    switch (status) {
        case 200:
            return "OK";
        case 404:
            return "Not Found";
        case 500:;
        default:;
    }
    return "Internal Server Error";
}

typedef struct Response {
    char *content;
    size_t content_alloc_size;
    size_t body_size;
    size_t size;
    uint32_t status;
    char *reason;
    char *mimetype;
} Response;

Response *response_html_new(uint32_t status, const char *body, size_t body_size) {
    Response *resp = mem_alloc(sizeof(Response));
    resp->content_alloc_size = strlen(http_response_fmt) + body_size + HEADER_EXTRA_SIZE;
    resp->content = mem_alloc(resp->content_alloc_size);
    resp->body_size = body_size;
    resp->mimetype = MIMETYPE_HTML;
    resp->status = status;
    resp->reason = http_reason(status);
    resp->size = sprintf(resp->content, http_response_fmt, status, http_reason(status), resp->mimetype, body_size,
                         body);
    return resp;
}

void response_free(Response *resp) {
    mem_free(resp->content, resp->content_alloc_size);
    mem_free(resp, sizeof(Response));
}

////////////////////////////// LUA ///////////////////////////////////////////
lua_State *lua_init() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    return L;
}

// pushing a table with the request method, path and headers
void request_to_lua_arg(lua_State *L, Request *r) {
    lua_newtable(L);
    lua_pushstring(L, r->method);
    lua_setfield(L, 2, "method");
    lua_pushstring(L, r->path);
    lua_setfield(L, 2, "path");

    lua_newtable(L);
    for (size_t h = 0; h < r->header_count; h++) {
        KeyValue *kv = r->headers[h];
        lua_pushstring(L, kv->value);
        lua_setfield(L, 3, kv->key);
    }
    lua_setfield(L, 2, "headers");
}

Response *response_from_lua(lua_State *L) {
    lua_Integer status = luaL_checkinteger(L, 1); // first returned value
    size_t body_sz;
    const char *body = luaL_checklstring(L, 2, &body_sz); // second returned value
    return response_html_new(status, body, body_sz);
}

void lua_log_error(lua_State *L) {
    LOG_ERR("lua: %s", lua_tostring(L, lua_gettop(L)));
    lua_pop(L, lua_gettop(L));
}

///////////////////////// NETWORKING /////////////////////////////////////////

typedef struct Client {
    int fd;
    struct sockaddr_in addr;
    size_t size;
    char *ip;
} Client;

void client_free(Client *c) {
    if (c->fd != -1)
        close(c->fd);
    mem_free(c, sizeof(Client));
}

typedef struct HTTPServer {
    int socket_fd;
    struct sockaddr_in server_addr;
    char *ip;
} HTTPServer;

HTTPServer *httpserver_new(int port) {
    HTTPServer *srv = mem_alloc(sizeof(HTTPServer));
    srv->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    srv->server_addr.sin_family = AF_INET;
    srv->server_addr.sin_addr.s_addr = INADDR_ANY;
    srv->server_addr.sin_port = htons(port);
    return srv;
}

void httpserver_free(HTTPServer *srv) {
    if (srv == NULL)
        return;

    if (srv->socket_fd != -1)
        close(srv->socket_fd);

    mem_free(srv, sizeof(HTTPServer));
}

int http_server_listen(HTTPServer *srv, int maxconnections) {
    int err = bind(srv->socket_fd, (struct sockaddr *) &srv->server_addr, sizeof(srv->server_addr));
    if (err == -1) {
        LOG_ERR("it wasn't possible to bind port %d", ntohs(srv->server_addr.sin_port));
        exit(1);
    }
    return listen(srv->socket_fd, maxconnections);
}

Client *http_server_accept(HTTPServer *srv) {
    Client *c = mem_alloc(sizeof(Client));

    c->size = sizeof(struct sockaddr_in);
    c->fd = accept(srv->socket_fd, (struct sockaddr *) &c->addr, (socklen_t *) &c->size);
    if (c->fd == -1) {
        panic("accept");
    }
    c->ip = inet_ntoa(c->addr.sin_addr);

    int flags = fcntl(c->fd, F_GETFL, 0);
    fcntl(c->fd, F_SETFL, flags | O_NONBLOCK);

    return c;
}

Request *http_read_request(Client *client) {
    size_t request_buff_size = sizeof(char) * REQUEST_HEADER_SIZE;
    char *request_buff = mem_alloc(request_buff_size);
    size_t request_sz;
    request_sz = recv(client->fd, request_buff, REQUEST_HEADER_SIZE, 0);
    Request *r = request_new(request_buff);
    r->size = request_sz;
    mem_free(request_buff, request_buff_size);
    return r;
}

void response_write(Client *client, Response *resp) {
    write(client->fd, resp->content, resp->size);
}

////////////////////////// MAIN //////////////////////////////////////////////

void client_worker(Client *client) {
    Request *r = http_read_request(client);
    LOG_INFO("Request: %s %s", r->method, r->path);

    lua_State *L = lua_init();
    if (luaL_dofile(L, SCRIPT_FILENAME) == LUA_OK) {
        lua_getglobal(L, SCRIPT_ENTRYPOINT);
        request_to_lua_arg(L, r);
        if (lua_pcall(L, 1, LUA_MULTRET, 0) == LUA_OK) {
            Response *resp = response_from_lua(L);
            response_write(client, resp);
            LOG_OK("Response: %d %s", resp->status, resp->reason);
            response_free(resp);
        } else {
            lua_log_error(L);
        }
    } else {
        lua_log_error(L);
    }

    request_free(r);
    client_free(client);
    lua_close(L);
}

int main(int argc, char **argv) {
    HTTPServer *server = NULL;

    // https://man7.org/linux/man-pages/man2/signalfd.2.html
    sigset_t mask;
    int sfd;
    struct signalfd_siginfo fdsi;
    ssize_t s;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGKILL);
    sigaddset(&mask, SIGTERM);
    sigaddset(&mask, SIGQUIT);
    if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1) {
        panic("sigprocmask");
    }
    sfd = signalfd(-1, &mask, 0);
    if (sfd == -1) {
        panic("signalfd");
    }

    server = httpserver_new(HTTP_PORT);
    http_server_listen(server, MAX_CONNECTIONS);
    LOG_INFO("listening http://localhost:%d", HTTP_PORT);

    // https://man7.org/linux/man-pages/man7/epoll.7.html
    struct epoll_event ev, sig_ev, events[MAX_CONNECTIONS];
    int nfds, epollfd;

    epollfd = epoll_create1(0);
    if (epollfd == -1) {
        panic("error on creating epoll descriptor");
    }

    ev.events = EPOLLIN;
    ev.data.fd = server->socket_fd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, server->socket_fd, &ev) == -1) {
        panic("epoll_ctl: listen_sock");
    }

    sig_ev.events = EPOLLIN;
    sig_ev.data.fd = sfd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, sfd, &sig_ev) == -1) {
        panic("epoll_ctl: signals");
    }

    while (1) {
        nfds = epoll_wait(epollfd, events, MAX_CONNECTIONS, -1);
        if (nfds == -1) {
            panic("epoll_wait");
        }

        for (int n = 0; n < nfds; ++n) {
            if (events[n].data.fd == server->socket_fd) {
                Client *client = http_server_accept(server);
                if (client->fd == -1) {
                    client_free(client);
                    continue;
                }
                LOG_INFO("client %s connected", client->ip);
                ev.events = EPOLLIN | EPOLLET;
                ev.data.ptr = client;
                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, client->fd, &ev) == -1) {
                    panic("epoll_ctl: client socket");
                }
            } else if (events[n].data.fd == sfd) {
                s = read(sfd, &fdsi, sizeof(fdsi));
                if (s != sizeof(fdsi)) {
                    panic("signal: read");
                }
                switch (fdsi.ssi_signo) {
                    default:
                        goto quit_server;
                }
            } else {
                client_worker(events[n].data.ptr);
            }
        }
    }

    quit_server:
    httpserver_free(server);
    LOG_INFO("%s", "gracefully terminating.");
    fflush(stderr);
    fflush(stdout);

    return EXIT_SUCCESS;
}
