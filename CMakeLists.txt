cmake_minimum_required(VERSION 3.5)
project(cson)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -std=c11")

set(CSON_HEARDER_FILES
        src/cson.h
        src/clist.h src/cmap.h)

set(CSON_SOURCE_FILES
        src/cson.c
        main.c src/clist.c src/cmap.c)
add_executable(cson ${CSON_HEARDER_FILES} ${CSON_SOURCE_FILES})