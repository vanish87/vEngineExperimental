
set(RESOURCE_SRC ${CMAKE_CURRENT_SOURCE_DIR})
set(RESOURCE_BIN ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(BIN_FILES)


file(GLOB SHADER_VS_SOURCE "${RESOURCE_SRC}/shader/vs/*.hlsl")
foreach(SRC_FILE ${SHADER_VS_SOURCE})
  get_filename_component(BIN_FILE ${SRC_FILE} NAME_WE)
  set(BIN_FILE ${RESOURCE_BIN}/shader/vs/${BIN_FILE}.json)

  set(BIN_FILES ${BIN_FILES} ${BIN_FILE})
  add_custom_command(
    OUTPUT ${BIN_FILE}
    DEPENDS ${SRC_FILE} shader_compiler
    COMMAND shader_compiler -i ${SRC_FILE} -o ${BIN_FILE} -p vs -r ${RESOURCE_SRC} -b ${RESOURCE_BIN}
    COMMENT "Compile vs ${SRC_FILE} to json ${BIN_FILE}"
  )
endforeach(SRC_FILE ${SHADER_VS_SOURCE})

file(GLOB SHADER_PS_SOURCE "${RESOURCE_SRC}/shader/ps/*.hlsl")
foreach(SRC_FILE ${SHADER_PS_SOURCE})
  get_filename_component(BIN_FILE ${SRC_FILE} NAME_WE)
  set(BIN_FILE ${RESOURCE_BIN}/shader/ps/${BIN_FILE}.json)

  set(BIN_FILES ${BIN_FILES} ${BIN_FILE})
  add_custom_command(
    OUTPUT ${BIN_FILE}
    DEPENDS ${SRC_FILE} shader_compiler
    COMMAND shader_compiler -i ${SRC_FILE} -o ${BIN_FILE} -p ps -r ${RESOURCE_SRC} -b ${RESOURCE_BIN}
    COMMENT "Compile ps ${SRC_FILE} to json ${BIN_FILE}"
  )
endforeach(SRC_FILE ${SHADER_PS_SOURCE})

file(GLOB SMPL_SOURCE "${RESOURCE_SRC}/smpl/*.smpl")
foreach(SRC_FILE ${SMPL_SOURCE})
  get_filename_component(BIN_FILE ${SRC_FILE} NAME_WE)
  set(BIN_FILE ${RESOURCE_BIN}/smpl/${BIN_FILE}.json)

  set(BIN_FILES ${BIN_FILES} ${BIN_FILE})
  add_custom_command(
    OUTPUT ${BIN_FILE}
    DEPENDS ${SRC_FILE} smpl_to_json
    COMMAND smpl_to_json -i ${SRC_FILE} -o ${BIN_FILE}
    COMMENT "Covert smpl ${SRC_FILE} to json ${BIN_FILE}"
    # ${CMAKE_SOURCE_DIR}/resources
    # $<TARGET_FILE_DIR:resource>/resources
  )
endforeach(SRC_FILE ${SMPL_SOURCE})

file(GLOB ASSIMP_SOURCE "${RESOURCE_SRC}/boblamp/*.md5mesh")
foreach(SRC_FILE ${ASSIMP_SOURCE})
  get_filename_component(BIN_FILE ${SRC_FILE} NAME_WE)
  set(BIN_FILE ${RESOURCE_BIN}/assimp/${BIN_FILE}.json)

  set(BIN_FILES ${BIN_FILES} ${BIN_FILE})
  add_custom_command(
    OUTPUT ${BIN_FILE}
    DEPENDS ${SRC_FILE} assimp_to_json
    COMMAND assimp_to_json -i ${SRC_FILE} -o ${BIN_FILE} -r ${RESOURCE_SRC} -b ${RESOURCE_BIN}
    COMMENT "Covert assimp ${SRC_FILE} to json ${BIN_FILE}"
    # ${CMAKE_SOURCE_DIR}/resources
    # $<TARGET_FILE_DIR:resource>/resources
  )
endforeach(SRC_FILE ${SMPL_SOURCE})
# set(path_test ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$<CONFIG:Debug>)
# message(STATUS "${SMPL_SOURCE}")
# message(STATUS "${BIN_FILES}")

# add_custom_target(
#   resource ALL
#   DEPENDS ${BIN_FILES}
# )

add_custom_target(
  remove-all ALL
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${RESOURCE_BIN}
  COMMENT "Clean ${RESOURCE_BIN}"
)
  
add_custom_target(
  resource-copy ALL
  DEPENDS ${BIN_FILES}
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${RESOURCE_BIN}
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/resource
  COMMENT "Copy ${RESOURCE_BIN} to ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/resource"
)
# add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#     ${CMAKE_SOURCE_DIR}/resource
#     $<TARGET_FILE_DIR:${PROJECT_NAME}>/resource
# )