cmake_minimum_required(VERSION 2.8.11)
project(http-lua)

set(CMAKE_C_FLAGS "-Wall -std=c99 -ggdb ${CMAKE_C_FLAGS}")

find_package(Lua REQUIRED)
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.c)

configure_file(
        app/app.lua
        ${CMAKE_CURRENT_BINARY_DIR}/app/app.lua
        COPYONLY
)

configure_file(
        static/http-lua.svg
        ${CMAKE_CURRENT_BINARY_DIR}/app/static/http-lua.svg
        COPYONLY
)

include_directories(
        ${LUA_INCLUDE_DIR}
        "include/"
)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME}
        ${LUA_LIBRARIES}
        )
