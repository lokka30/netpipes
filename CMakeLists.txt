cmake_minimum_required(VERSION 3.30)

project(NetPipes)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

set(SOURCES
    src/netpipes.c
    src/coords.c
    src/items.c
    src/rce.c
)

set(CMAKE_BUILD_TYPE Debug)  # or Release
add_executable(netpipes ${SOURCES})
