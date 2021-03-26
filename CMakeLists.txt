project(colourfu C CXX)

cmake_minimum_required(VERSION 3.17)

set(SOURCES
        src/main.c)

add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE vendor/stb)

add_executable(colourfu
        ${SOURCES})

target_link_libraries(colourfu stb_image)