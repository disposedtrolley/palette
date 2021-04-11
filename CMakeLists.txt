project(palette C)

cmake_minimum_required(VERSION 3.17)

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -DUNITY_INCLUDE_DOUBLE -DUNITY_DOUBLE_PRECISION=1e-12")

# STB
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE vendor/stb)

# Unity test framework
add_library(unity STATIC vendor/Unity/src/unity.c)
target_include_directories(unity PUBLIC vendor/Unity/src)

# Internal libraries
add_library(lib STATIC
        lib/colour.c
        lib/image.c)
target_include_directories(lib PUBLIC lib)
target_link_libraries(lib stb)

# Main executable
add_executable(palette
        main.c)

target_link_libraries(palette lib stb)

# Test executable
include(CTest)

add_executable(colour_test
        tests/colour_test.c)
target_link_libraries(colour_test lib unity)

add_executable(image_test
        tests/image_test.c)
target_link_libraries(image_test lib unity)

add_test(palette image_test colour_test)

configure_file(tests/_DSF0914.jpg _DSF0914.jpg COPYONLY)