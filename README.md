![](static/http-lua.svg)

# http-lua

> HTTP Server in C for single Lua application with epoll support.

The project is intended to be a reference for articles that I am writing for my blog. It is a small **HTTP server** in
**C** that uses **epoll**, **signalfd**, and **embedded Lua**. The idea is to be used as a standalone application
server. It can be used for study purposes, to serve as a reference, and for fun.

## Articles linked to this repository

- [More Advanced Examples of Embedding Lua in C](https://lucasklassmann.com/blog/2023-02-26-more-advanced-examples-of-embedding-lua-in-c/)

## Features

- Support basic HTTP requests and responses
- Application written in Lua. Change app.lua script.
- Event control with epoll() for signals and socket
- Tested with 2048 clients connected per second (tested with Apache Benchmark ab)

## TODO

- Remove the fixed date time in the HTTP responses
- Improve memory management
- Add arguments options to
    - change port
    - max connections
    - script file
    - script entrypoint

## Dependencies

    - CMake >= 2.8.11
    - Lua 5.3
    - epoll (libc)

## Building

On Linux with CMake, by default, it will use Makefile. Go inside the project's folder:

```bash
mkdir build
cd build
cmake ..
make
```

## License

[Apache 2.0](LICENSE)
