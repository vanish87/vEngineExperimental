

# Set the project name
project (vengine)

# Add a library with the above sources
# add_library(${PROJECT_NAME} src/vector.cpp)
# add_library(engine::core ALIAS ${PROJECT_NAME})

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/core core_source)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/rendering rendering_source)

# if(APPLE)
#     aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/core/apple apple_sources)
# endif()

add_library(${PROJECT_NAME} 
    ${core_source}
    ${rendering_source}
    # ${apple_sources}
)
add_library(engine::core ALIAS ${PROJECT_NAME})

set(HEADER_NAME ${PROJECT_NAME})
string(TOUPPER ${HEADER_NAME} HEADER_NAME)

message(STATUS "CMAKE_BINARY_DIR= ${CMAKE_BINARY_DIR}")
message(STATUS "ASSIMP_INCLUDE_DIR= ${ASSIMP_INCLUDE_DIR}")

GENERATE_EXPORT_HEADER( ${PROJECT_NAME}
             BASE_NAME ${HEADER_NAME}
             EXPORT_MACRO_NAME ${HEADER_NAME}_API
             EXPORT_FILE_NAME ${API_EXPORT_DIR}/${HEADER_NAME}_API.h
             STATIC_DEFINE ${HEADER_NAME}_BUILT_AS_STATIC
)

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${ASSIMP_INCLUDE_DIR}
)

target_link_libraries( ${PROJECT_NAME}
	${ASSIMP_LIBRARIES}
	# ${LUA_LIBRARIES}
	# ${FREETYPE_LIBRARIES}
)

if(UNIX)
target_link_libraries( ${PROJECT_NAME}
    # ${CMKAE_DL_LIBS}
    dl
)
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${EXTERNAL_BUILD_DIR}/bin
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/include/vengine/rendering/shared
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/shader
)
# INSTALL(TARGETS ${PROJECT_NAME} 
#         PUBLIC_HEADER DESTINATION $<TARGET_FILE_DIR:${PROJECT_NAME}
# )

if(APPLE)
    # add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    #     COMMAND ${CMAKE_COMMAND} -E copy_directory
    #     "${EXTERNAL_BUILD_DIR}/lib"
    #     $<TARGET_FILE_DIR:${PROJECT_NAME}>/../lib
    # )
endif(APPLE)