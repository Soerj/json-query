cmake_minimum_required(VERSION 3.10)

project(json-query C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

set(SOURCES
    src/main.c
    src/query.c
    src/parser.c
    src/utils.c
)

add_executable(json-query ${SOURCES})
