

if(WIN32)
    add_subdirectory(shader_compiler)
    add_subdirectory(smpl_to_json)
    add_subdirectory(assimp_to_json)
endif(WIN32)

# add_custom_target(resource)

# add_custom_command(
#     OUTPUT my.json
#     COMMAND smpl_to_json -a -t
#     COMMENT "smpl json"
#     # ${CMAKE_SOURCE_DIR}/resources
#     # $<TARGET_FILE_DIR:resource>/resources
# )
# # set(path_test ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$<CONFIG:Debug>)
# # message(STATUS "LIBRARY_OUTPUT_DIRECTORY = ${path_test}")

# add_custom_target(
#   resources ALL
#   DEPENDS my.json
# )
# message(STATUS $<TARGET_FILE_DIR:resource>)