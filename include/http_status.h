//
// Created by Lucas Klassmann on 23/05/22.
//
#ifndef HTTP_STATUS_H
#define HTTP_STATUS_H

#include <stdio.h>

#define HTTP_STATUS_CODE_TABLE_SIZE 512
static const char *http_status_codes_reason[HTTP_STATUS_CODE_TABLE_SIZE] = {
        NULL,                                        // NULL
        NULL,                                        // NULL
        NULL,                                        // NULL
        NULL,                                        // NULL
        NULL,                                        // NULL
        NULL,                                        // NULL
        NULL,                                        // NULL
        NULL,                                        // NULL
        NULL,                                        // NULL
        NULL,                                        // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        NULL,                                       // NULL
        "Continue",                                // 100
        "Switching Protocols",                     // 101
        "Processing",                              // 102
        "Early Hints",                             // 103  # see RFC 8297
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        "OK",                                      // 200
        "Created",                                 // 201
        "Accepted",                                // 202
        "Non Authoritative Information",           // 203
        "No Content",                              // 204
        "Reset Content",                           // 205
        "Partial Content",                         // 206
        "Multi Status",                            // 207
        "Already Reported",                        // 208  # see RFC 5842
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        "IM Used",                                 // 226  # see RFC 3229
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        "Multiple Choices",                        // 300
        "Moved Permanently",                       // 301
        "Found",                                   // 302
        "See Other",                               // 303
        "Not Modified",                            // 304
        "Use Proxy",                               // 305
        "Switch Proxy",                            // 306  # unused
        "Temporary Redirect",                      // 307
        "Permanent Redirect",                      // 308
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        "Bad Request",                             // 400
        "Unauthorized",                            // 401
        "Payment Required",                        // 402  # unused
        "Forbidden",                               // 403
        "Not Found",                               // 404
        "Method Not Allowed",                      // 405
        "Not Acceptable",                          // 406
        "Proxy Authentication Required",           // 407
        "Request Timeout",                         // 408
        "Conflict",                                // 409
        "Gone",                                    // 410
        "Length Required",                         // 411
        "Precondition Failed",                     // 412
        "Request Entity Too Large",                // 413
        "Request URI Too Long",                    // 414
        "Unsupported Media Type",                  // 415
        "Requested Range Not Satisfiable",         // 416
        "Expectation Failed",                      // 417
        "I'm a teapot",                            // 418  # see RFC 2324
        NULL,                                      // NULL
        NULL,                                      // NULL
        "Misdirected Request",                     // 421  # see RFC 7540
        "Unprocessable Entity",                    // 422
        "Locked",                                  // 423
        "Failed Dependency",                       // 424
        "Too Early",                               // 425  # see RFC 8470
        "Upgrade Required",                        // 426
        NULL,                                      // NULL
        "Precondition Required",                   // 428  # see RFC 6585
        "Too Many Requests",                       // 429
        NULL,                                      // NULL
        "Request Header Fields Too Large",         // 431
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        "Retry With",                              // 449  # proprietary MS extension
        NULL,                                      // NULL
        "Unavailable For Legal Reasons",           // 451
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        NULL,                                      // NULL
        "Internal Server Error",                   // 500
        "Not Implemented",                         // 501
        "Bad Gateway",                             // 502
        "Service Unavailable",                     // 503
        "Gateway Timeout",                         // 504
        "HTTP Version Not Supported",              // 505
        "Variant Also Negotiates",                 // 506  # see RFC 2295
        "Insufficient Storage",                    // 507
        "Loop Detected",                           // 508  # see RFC 5842
        NULL,                                      // NULL
        "Not Extended",                            // 510
        "Network Authentication Failed",           // 511
};

const char * http_status_reason(unsigned int status_code) {
    if (status_code < HTTP_STATUS_CODE_TABLE_SIZE) {
        return http_status_codes_reason[status_code];
    }
    return NULL;
}

#endif //HTTP_STATUS_H
