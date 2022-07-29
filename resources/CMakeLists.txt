
add_custom_command(
    OUTPUT my.json
    COMMAND smpl_to_json -s 
    COMMENT "smpl json"
    # ${CMAKE_SOURCE_DIR}/resources
    # $<TARGET_FILE_DIR:resource>/resources
)
# set(path_test ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$<CONFIG:Debug>)
# message(STATUS "LIBRARY_OUTPUT_DIRECTORY = ${path_test}")

add_custom_target(
  resources ALL
  DEPENDS my.json
)