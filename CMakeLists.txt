cmake_minimum_required(VERSION 3.5)
project(cson)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -std=c11")

set(CSON_HEARDER_FILES
        cson.h
        clist.h)

set(CSON_SOURCE_FILES
        cson.c
        main.c clist.c)
add_executable(cson ${CSON_HEARDER_FILES} ${CSON_SOURCE_FILES})