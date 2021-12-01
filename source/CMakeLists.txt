find_package(lua)

include_directories(${LUA_INCLUDE_DIR})

# add all files in source folder to SRC
# aux_source_directory(source SRC)

# complie all files in SRC as vEngine exe
add_executable(vEngine main.cpp)

message(STATUS "LUA_LIBRARIES = ${LUA_LIBRARIES}")

target_link_libraries(vEngine ${LUA_LIBRARIES})