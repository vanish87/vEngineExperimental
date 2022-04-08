
set(EXTERNAL_BUILD_DIR "${CMAKE_BINARY_DIR}/external/build")
#set(EXTERNAL_PRE_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source/ExternalLibs/ManualBuild")

message(STATUS "EXTERNAL_BUILD_DIR= ${EXTERNAL_BUILD_DIR}")

find_package(assimp REQUIRED)
# find_package(lua REQUIRED)
# find_package(freetype REQUIRED)

# include_directories(${LUA_INCLUDE_DIR})
# include_directories(${FREETYPE_INCLUDE_DIR})

# add all files in source folder to SRC
# aux_source_directory(source SRC)

add_subdirectory(configure)
add_subdirectory(engine)
add_subdirectory(plugins)
add_subdirectory(app)
add_subdirectory(editor)
add_subdirectory(test)
add_subdirectory(document)
