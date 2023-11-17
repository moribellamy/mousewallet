cmake_minimum_required(VERSION 3.26)
project(mousewallet C)
enable_testing()

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS OFF)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif ()

# Configure external deps
set(BUILD_SHARED_LIBS OFF)
set(SECP256K1_BUILD_TESTS OFF)
set(SECP256K1_BUILD_EXHAUSTIVE_TESTS OFF)
set(SECP256K1_BUILD_CTIME_TESTS OFF)
add_subdirectory("vendor/secp256k1")
add_library(argparse STATIC vendor/argparse/argparse.c)
add_library(sha3 STATIC vendor/SHA3IUF/sha3.c)

# Lib
add_library(lib STATIC src/lib.c)
target_link_libraries(lib sha3 secp256k1)
target_include_directories(lib PRIVATE vendor/secp256k1/include)

# Main
add_executable(mousewallet src/main.c)
target_link_libraries(mousewallet PRIVATE argparse lib)

# Test
add_executable(test_mousewallet src/tests.c)
target_link_libraries(test_mousewallet PRIVATE lib)

add_test(NAME MousewalletTest COMMAND test_mousewallet)