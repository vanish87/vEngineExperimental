# cmake minium version required
cmake_minimum_required(VERSION 3.13)

# cmake setting
set(CMAKE_VERBOSE_MAKEFILE ON)
include(GenerateExportHeader)
# Include cmake modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# project setting
project(vEngine)

# c++ setting
set(CMAKE_CXX_STANDARD 14)
# lib setting
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# include setting
# set configure include path
set(CONFIGURE_INCLUDE "${CMAKE_BINARY_DIR}/configure/include")
set(API_EXPORT_DIR "${CMAKE_BINARY_DIR}/api")
include_directories(include)
include_directories(${CONFIGURE_INCLUDE})
include_directories(${API_EXPORT_DIR})


# output setting
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# debug setting
set(CMAKE_DEBUG_POSTFIX d)

if(WIN32)
add_compile_definitions(WINDOWS)
elseif(UNIX)
add_compile_definitions(LINUX)
endif()

add_subdirectory(source)