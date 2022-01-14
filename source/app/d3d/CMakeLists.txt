project(example_d3d)

# Create the executable
add_executable(${PROJECT_NAME} main.cpp interface.cpp)

# Link the static library from subproject1 using its alias sub::lib1
# Link the header only library from subproject2 using its alias sub::lib2
# This will cause the include directories for that target to be added to this project
target_link_libraries(${PROJECT_NAME}
    engine::core
    d3d11.lib
    dxgi.lib
)


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${EXTERNAL_BUILD_DIR}/bin"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)