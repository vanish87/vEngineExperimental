
project(opengl_app)


# Create the executable
add_executable(${PROJECT_NAME} ${PROJECT_NAME}_main.cpp)

target_link_libraries(${PROJECT_NAME}
    engine::core
)

if(UNIX)
    target_link_libraries(${PROJECT_NAME} pthread)
endif(UNIX)

# add_compile_options(-pthread)

# copy dll files to runtime directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${EXTERNAL_BUILD_DIR}/bin"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)