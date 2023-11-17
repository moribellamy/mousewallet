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
        pcg_obj_build
        SOURCE_DIR "${PCG_PATH}/src"
        CONFIGURE_COMMAND ""  # No configure step
        BUILD_COMMAND "${MAKE}"
        BUILD_IN_SOURCE 1     # Build in source tree
        INSTALL_COMMAND ""    # No install step
)
add_library(pcg_objects STATIC IMPORTED)
set_target_properties(pcg_objects PROPERTIES IMPORTED_LOCATION "${PCG_PATH}/src/libpcg_random.a")
add_library(pcg_extras STATIC ${PCG_PATH}/extras/entropy.c)
target_include_directories(pcg_extras PRIVATE ${PCG_PATH}/include)
target_link_libraries(pcg_extras pcg_objects)

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
add_library(keccak STATIC vendor/SHA3IUF/sha3.c)

# ---------------
# Mousewallet Lib
# ---------------
add_library(lib STATIC src/lib.c src/lib.h)
add_dependencies(lib pcg_obj_build)
target_link_libraries(lib keccak secp256k1 pcg_objects pcg_extras)

# ---------------
# Mousewallet CLI
# ---------------
add_executable(mousewallet src/main.c)
add_dependencies(mousewallet pcg_obj_build)
target_link_libraries(mousewallet PRIVATE argparse lib pcg_objects)

# -----------------
# Mousewallet Tests
# -----------------
add_executable(test_mousewallet src/tests.c)
target_link_libraries(test_mousewallet PRIVATE lib)
