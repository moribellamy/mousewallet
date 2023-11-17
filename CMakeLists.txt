cmake_minimum_required(VERSION 3.26)
project(mousewallet C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS OFF)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif ()

# ----------------
# PCG Random Suite
# ----------------
include(ExternalProject)
set(PCG_PATH "${CMAKE_SOURCE_DIR}/vendor/pcg-c")
ExternalProject_Add(
        pcg
        SOURCE_DIR ${PCG_PATH}
        CONFIGURE_COMMAND ""  # No configure step
        BUILD_COMMAND make
        BUILD_IN_SOURCE 1     # Build in source tree
        INSTALL_COMMAND ""    # No install step
)
add_library(pcg_interface INTERFACE)
add_dependencies(pcg_interface pcg)
# find src extras -name *.o
target_sources(pcg_interface INTERFACE
        ${PCG_PATH}/src/pcg-rngs-64.o
        ${PCG_PATH}/src/pcg-output-32.o
        ${PCG_PATH}/src/pcg-advance-32.o
        ${PCG_PATH}/src/pcg-output-8.o
        ${PCG_PATH}/src/pcg-global-64.o
        ${PCG_PATH}/src/pcg-rngs-16.o
        ${PCG_PATH}/src/pcg-advance-8.o
        ${PCG_PATH}/src/pcg-advance-128.o
        ${PCG_PATH}/src/pcg-rngs-128.o
        ${PCG_PATH}/src/pcg-advance-64.o
        ${PCG_PATH}/src/pcg-output-64.o
        ${PCG_PATH}/src/pcg-rngs-32.o
        ${PCG_PATH}/src/pcg-output-16.o
        ${PCG_PATH}/src/pcg-advance-16.o
        ${PCG_PATH}/src/pcg-output-128.o
        ${PCG_PATH}/src/pcg-rngs-8.o
        ${PCG_PATH}/src/pcg-global-32.o
        ${PCG_PATH}/extras/entropy.o
)
target_include_directories(pcg_interface INTERFACE
        ${PCG_PATH}/include
        ${PCG_PATH}/extras
)

# --------------------
# SECP256k1 curve math
# --------------------
set(BUILD_SHARED_LIBS OFF)
set(SECP256K1_BUILD_TESTS OFF)
set(SECP256K1_BUILD_EXHAUSTIVE_TESTS OFF)
set(SECP256K1_BUILD_CTIME_TESTS OFF)
add_subdirectory(vendor/secp256k1)

# -------------------
# Argparse and Keccak
# -------------------
add_library(argparse STATIC vendor/argparse/argparse.c)
add_library(sha3 STATIC vendor/SHA3IUF/sha3.c)

# ---------------
# Mousewallet Lib
# ---------------
add_library(lib STATIC src/lib.c src/lib.h)
add_dependencies(lib pcg)
target_link_libraries(lib sha3 secp256k1 pcg_interface)

# ---------------
# Mousewallet CLI
# ---------------
add_executable(mousewallet src/main.c)
target_link_libraries(mousewallet PRIVATE argparse lib)

# -----------------
# Mousewallet Tests
# -----------------
add_executable(test_mousewallet src/tests.c)
target_link_libraries(test_mousewallet PRIVATE lib)
