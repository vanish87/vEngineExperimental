

# Set the project name
project (empty_plugin)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source empty_source)

add_library(${PROJECT_NAME} ${empty_source})

add_library(engine::empty_plugin ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${vengine_SOURCE_DIR}/include
)

target_link_libraries( ${PROJECT_NAME}
    engine::core
)