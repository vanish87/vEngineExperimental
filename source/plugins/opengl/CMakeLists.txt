
# Set the project name
project (opengl_rendering_plugin)

find_package(glfw REQUIRED)

# Add a library with the above sources
# add_library(${PROJECT_NAME} src/vector.cpp)
# add_library(engine::core ALIAS ${PROJECT_NAME})

add_library(${PROJECT_NAME}
    src/opengl_render_engine.cpp
    )
add_library(engine::opengl_rendering_plugin ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${vengine_SOURCE_DIR}/include
    PUBLIC ${GLFW_INCLUDE_DIR}
)

# add_dependencies(${PROJECT_NAME} engine::rendering)

target_link_libraries( ${PROJECT_NAME}
    engine::core
    ${GLFW_LIBRARIES}
)
