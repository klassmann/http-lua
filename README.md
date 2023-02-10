# http-lua
Single Lua Application HTTP Server in C with epoll support.

This project was created to be used as a reference to some articles that I am writing on my blog.

I wrote a http server to show how Lua can be used to allow the user customize a real application.

My articles that refers to this repository:
    - 

## Features
    - Support basic HTTP requests and responses
    - Lua application written in the app.lua script
    - event controlling with epoll() for signals and socket
    - 2048 clients connected per second (I just tested with Apache Benchmark ab)

## Dependencies
    - CMake
    - Lua 5.3
    - epoll (libc)

## Building
On Linux with CMake, by default it will use Makefile.
```bash
mkdir build
cd build
cmake ..
make
```