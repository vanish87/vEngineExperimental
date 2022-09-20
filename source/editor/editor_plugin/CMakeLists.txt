# Set the project name
project (editor_plugin)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src sources)

add_library(${PROJECT_NAME} 
	${sources}
)
add_library(engine::editor_plugin ALIAS ${PROJECT_NAME})

set(HEADER_NAME ${PROJECT_NAME})
string(TOUPPER ${HEADER_NAME} HEADER_NAME)

message(STATUS "CMAKE_BINARY_DIR= ${CMAKE_BINARY_DIR}")

GENERATE_EXPORT_HEADER( ${PROJECT_NAME}
             BASE_NAME ${HEADER_NAME}
             EXPORT_MACRO_NAME ${HEADER_NAME}_API
             EXPORT_FILE_NAME ${API_EXPORT_DIR}/${HEADER_NAME}_API.h
             STATIC_DEFINE ${HEADER_NAME}_BUILT_AS_STATIC
)

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${vengine_SOURCE_DIR}/include
)

target_link_libraries( ${PROJECT_NAME}
    engine::core
)