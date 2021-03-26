project(colourfu C)

cmake_minimum_required(VERSION 3.17)

set(SOURCES
        src/main.c)

add_executable(colourfu
        ${SOURCES})