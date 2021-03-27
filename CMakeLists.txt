project(colourfu C)

cmake_minimum_required(VERSION 3.17)

set(SOURCES
        src/main.c)

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE vendor/stb)

add_executable(colourfu
        ${SOURCES})

target_link_libraries(colourfu stb)