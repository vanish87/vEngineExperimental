
# Set the project name
project (d3d11_rendering_plugin)

# Add a library with the above sources
# add_library(${PROJECT_NAME} src/vector.cpp)
# add_library(engine::core ALIAS ${PROJECT_NAME})
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src d3d_source)

add_library(${PROJECT_NAME}
    ${d3d_source}
    )
add_library(engine::d3d11_rendering_plugin ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${vengine_SOURCE_DIR}/include
)

# add_dependencies(${PROJECT_NAME} engine::rendering)

target_link_libraries( ${PROJECT_NAME}
    engine::core
    d3d11.lib
    dxgi.lib
    d3dcompiler.lib
)
