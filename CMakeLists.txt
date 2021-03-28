project(colourfu C)

cmake_minimum_required(VERSION 3.17)

# STB
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE vendor/stb)

# Unity test framework
add_library(unity STATIC vendor/Unity/src/unity.c)
target_include_directories(unity PUBLIC vendor/Unity/src)

# Main executable
set(SOURCES
        src/main.c)

add_executable(colourfu
        ${SOURCES})

target_link_libraries(colourfu stb)

# Test executable
include(CTest)
add_executable(colourfu_test
        tests/test.c)

set_property(TARGET colourfu PROPERTY ENABLE_EXPORTS 1)  # Allow linking to the main executable.
target_link_libraries(colourfu_test colourfu unity)

add_test(colourfu colourfu_test)