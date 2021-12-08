
# Set the project name
project (rendering)

# Add a library with the above sources
# add_library(${PROJECT_NAME} src/vector.cpp)
# add_library(engine::core ALIAS ${PROJECT_NAME})

add_library(${PROJECT_NAME} 
    src/render_engine.cpp
    )
add_library(engine::rendering ALIAS ${PROJECT_NAME})

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
)

# target_link_libraries( ${PROJECT_NAME}
# ${LUA_LIBRARIES}
# ${FREETYPE_LIBRARIES})
