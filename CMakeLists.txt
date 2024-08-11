cmake_minimum_required(VERSION 3.10)

project(json-query C)

set(JANSSON_INCLUDE_DIR "/opt/homebrew/Cellar/jansson/2.14/include")
set(JANSSON_LIBRARY_DIR "/opt/homebrew/Cellar/jansson/2.14/lib")
set(JSONC_INCLUDE_DIR "/opt/homebrew/Cellar/json-c/0.17/include/json-c")
set(JSONC_LIBRARY_DIR "/opt/homebrew/Cellar/json-c/0.17/lib")
set(EXE_NAME "json-query")

# Find json-c library
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSON_C REQUIRED json-c)

include_directories(${JSON_C_INCLUDE_DIRS})
link_directories(${JSON_C_LIBRARY_DIRS})

include_directories(${JANSSON_INCLUDE_DIR})
link_directories(${JANSSON_LIBRARY_DIR})

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

set(SOURCES
    src/main.c
    src/query.c
    src/parser.c
    src/utils.c
)

add_executable(${EXE_NAME} ${SOURCES})

target_link_libraries(${EXE_NAME} jansson ${JSON_C_LIBRARIES})
