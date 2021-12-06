# cmake minium version required
cmake_minimum_required(VERSION 3.13)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CONFIGURE_INCLUDE "${CMAKE_CURRENT_BINARY_DIR}/configure/include")

# Include cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# project name
project(vEngine)

# c++ setting
set(CMAKE_CXX_STANDARD 11)

#include_directories(include)

include_directories(${CONFIGURE_INCLUDE})

add_subdirectory(source)