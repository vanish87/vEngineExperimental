# cmake minium version required
cmake_minimum_required(VERSION 3.8)

# Linux Build Command
# cmake -S . -B build_linux -DCMAKE_BUILD_TYPE=Debug
# cmake --build ./build_linux/

if(APPLE)
    set(VENGINE_BUILD_STATIC ON)
    set(VENGINE_BUILD_IOS ON)
    set(CMAKE_OSX_ARCHITECTURES arm64)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "13.0")
endif()

if(WIN32)
    set(VENGINE_BUILD_RESOURCE ON)
endif()

set(VENGINE_BUILD_DOC OFF)

# cmake setting
set(CMAKE_VERBOSE_MAKEFILE ON)

# Include cmake modules
include(GenerateExportHeader)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#Setup Git Rev
# ${GIT_REV}${GIT_DIFF}${GIT_TAG}${GIT_BRANCH}
include(GetGitRev)

# Meta information about the project
set(META_PROJECT_NAME        "vEngine")
set(META_PROJECT_DESCRIPTION "CMake Template")
set(META_AUTHOR_ORGANIZATION "")
set(META_AUTHOR_DOMAIN       "https://github.com/vanish87/")
set(META_AUTHOR_MAINTAINER   "vanish8.7@gmail.com")
set(META_VERSION_MAJOR       "0")
set(META_VERSION_MINOR       "0")
set(META_VERSION_PATCH       "1")
set(META_VERSION_REVISION    "${GIT_REV}")
set(META_VERSION             "${META_VERSION_MAJOR}.${META_VERSION_MINOR}.${META_VERSION_PATCH}")
set(META_NAME_VERSION        "${META_PROJECT_NAME} v${META_VERSION} (${META_VERSION_REVISION})")
set(META_CMAKE_INIT_SHA      "${GIT_REV}")

# project setting
project(vEngine)

if(VENGINE_BUILD_IOS)
    set(CMAKE_SYSTEM_NAME iOS)
    set(CMAKE_OSX_SYSROOT iphoneos)
endif()

# c++ setting
set(CMAKE_CXX_STANDARD 17)
if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
elseif(APPLE)
    # no warning as error for macos/metal build for now
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

# lib setting
if(VENGINE_BUILD_STATIC)
    option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
else()
    option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
endif()


# include setting
# set configure include path
set(CONFIGURE_INCLUDE ${CMAKE_BINARY_DIR}/configure/include)
set(API_EXPORT_DIR ${CMAKE_BINARY_DIR}/api)
include_directories(include)
include_directories(${CONFIGURE_INCLUDE})
include_directories(${API_EXPORT_DIR})


# output setting
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# debug setting
set(CMAKE_DEBUG_POSTFIX d)
add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")

set(PROJECT_NAME_U ${PROJECT_NAME})
string(TOUPPER ${PROJECT_NAME_U} PROJECT_NAME_U)

set(PROJECT_PLATFORM_MARCO ${PROJECT_NAME}_PLATFORM)
string(TOUPPER ${PROJECT_PLATFORM_MARCO} PROJECT_PLATFORM_MARCO)

if(WIN32)
    add_compile_definitions(${PROJECT_PLATFORM_MARCO}_WINDOWS)
elseif(APPLE)
    add_compile_definitions(${PROJECT_PLATFORM_MARCO}_APPLE)
elseif(UNIX)
    add_compile_definitions(${PROJECT_PLATFORM_MARCO}_UNIX)
endif()

if(VENGINE_BUILD_STATIC)
    add_compile_definitions(${PROJECT_NAME_U}_STATIC_LINK)
else()
    add_compile_definitions(${PROJECT_NAME_U}_DYNAMIC_LINK)
endif()

add_subdirectory(source)

if(VENGINE_BUILD_RESOURCE)
    add_subdirectory(resource)
endif()

# message(STATUS "CMAKE_SOURCE_DIR= ${CMAKE_SOURCE_DIR}")
# add_custom_target(COPY_RESOURCE ALL
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#     ${CMAKE_SOURCE_DIR}/resource
#     ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
# )
# add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#         COMMAND ${CMAKE_COMMAND} -E copy_directory
#         ${CMAKE_SOURCE_DIR}/resource
#         $<TARGET_FILE_DIR:${PROJECT_NAME}>/
# )