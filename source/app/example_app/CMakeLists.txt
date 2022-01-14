
project(example_app)

# Create the executable
add_executable(${PROJECT_NAME} main.cpp)

# Link the static library from subproject1 using its alias sub::lib1
# Link the header only library from subproject2 using its alias sub::lib2
# This will cause the include directories for that target to be added to this project
target_link_libraries(${PROJECT_NAME}
    engine::core
)

if(UNIX)
# static link opengl rendering for linux
target_link_libraries(${PROJECT_NAME}
    engine::opengl_rendering_plugin
)
endif()


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${EXTERNAL_BUILD_DIR}/bin"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)