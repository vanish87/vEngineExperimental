
# Set the project name
project (opengl_rendering_plugin)

find_package(glfw REQUIRED)

# Add a library with the above sources
# add_library(${PROJECT_NAME} src/vector.cpp)
# add_library(engine::core ALIAS ${PROJECT_NAME})
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source opengl_source)

add_library(${PROJECT_NAME}
    ${opengl_source}
    )
add_library(engine::opengl_rendering_plugin ALIAS ${PROJECT_NAME})

set(HEADER_NAME ${PROJECT_NAME})
string(TOUPPER ${HEADER_NAME} HEADER_NAME)

GENERATE_EXPORT_HEADER( ${PROJECT_NAME}
             BASE_NAME ${HEADER_NAME}
             EXPORT_MACRO_NAME ${HEADER_NAME}_API
             EXPORT_FILE_NAME ${API_EXPORT_DIR}/${HEADER_NAME}_API.hpp
             STATIC_DEFINE ${HEADER_NAME}_BUILT_AS_STATIC
)

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
