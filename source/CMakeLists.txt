find_package(lua)
find_package(freetype)

include_directories(${LUA_INCLUDE_DIR})
include_directories(${FREETYPE_INCLUDE_DIR})

# add all files in source folder to SRC
# aux_source_directory(source SRC)


message(STATUS "LUA_LIBRARIES = ${LUA_LIBRARIES}")
message(STATUS "FREETYPE_LIBRARIES = ${FREETYPE_LIBRARIES}")

# complie all files in SRC as vEngine exe
add_executable(vEngine main.cpp)

target_link_libraries(vEngine 
${LUA_LIBRARIES}
${FREETYPE_LIBRARIES})
