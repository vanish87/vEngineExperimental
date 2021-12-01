# cmake minium version required
cmake_minimum_required(VERSION 3.13)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(EXTERNAL_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/external/build")
#set(EXTERNAL_PRE_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source/ExternalLibs/ManualBuild")
# Include cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# project name
project(vEngine)

# c++ setting
set(CMAKE_CXX_STANDARD 11)

message(STATUS "EXTERNAL_BUILD_DIR= ${EXTERNAL_BUILD_DIR}")

message(STATUS "PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR = ${PROJECT_BINARY_DIR}")

include_directories(header)

add_subdirectory(source)