project(colourfu C)

cmake_minimum_required(VERSION 3.17)

# STB
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE vendor/stb)

# Unity test framework
add_library(unity STATIC vendor/Unity/src/unity.c)
target_include_directories(unity PUBLIC vendor/Unity/src)

# Internal libraries
add_library(lib STATIC lib/colour.c)
target_include_directories(lib PUBLIC lib)

# Main executable
add_executable(colourfu
        main.c)

target_link_libraries(colourfu lib stb)

# Test executable
include(CTest)
add_executable(colourfu_test
        tests/colour_test.c)

target_link_libraries(colourfu_test lib unity)

add_test(colourfu colourfu_test)