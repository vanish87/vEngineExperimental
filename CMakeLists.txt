# cmake minium version required
cmake_minimum_required(VERSION 3.13)

# project name
project(vEngine)

# c++ setting
set(CMAKE_CXX_STANDARD 11)


message(STATUS "PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR = ${PROJECT_BINARY_DIR}")

include_directories(header)
# add all files in source folder to SRC
aux_source_directory(source SRC)

# complie all files in SRC as vEngine exe
add_executable(vEngine ${SRC})
