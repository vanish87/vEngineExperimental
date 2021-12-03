# cmake minium version required
cmake_minimum_required(VERSION 3.13)

set(CMAKE_VERBOSE_MAKEFILE ON)

# Include cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# project name
project(vEngine)

# c++ setting
set(CMAKE_CXX_STANDARD 11)

#include_directories(include)

add_subdirectory(source)