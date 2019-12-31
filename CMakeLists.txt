cmake_minimum_required(VERSION 3.0)
project(formal_languages_hw1)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(WARNING "Do not build in-source. Please remove CMake cache, then build out-of-source.")
endif()

include("testing/CMakeLists.txt")
