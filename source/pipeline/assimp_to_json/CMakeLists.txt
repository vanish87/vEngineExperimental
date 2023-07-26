
project(assimp_to_json)

find_package(assimp REQUIRED)
# assimp needs zlib
set(ZLIB_ROOT ${EXTERNAL_BUILD_DIR})
find_package(zlib REQUIRED)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source source)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source/external external_source)

# Create the executable
add_executable(${PROJECT_NAME} 
    ${source}
    ${external_source}
)

add_dependencies(${PROJECT_NAME} engine::d3d11_rendering_plugin)

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${ASSIMP_INCLUDE_DIR}
)

# Link the static library from subproject1 using its alias sub::lib1
# Link the header only library from subproject2 using its alias sub::lib2
# This will cause the include directories for that target to be added to this project
target_link_libraries(${PROJECT_NAME}
    engine::core
	${ASSIMP_LIBRARIES}
	${ZLIB_LIBRARIES}
)
