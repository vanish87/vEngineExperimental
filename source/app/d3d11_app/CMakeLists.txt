
project(d3d11_app)

# Create the executable
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
    engine::core
)

# copy dll files to runtime directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${EXTERNAL_BUILD_DIR}/bin"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)