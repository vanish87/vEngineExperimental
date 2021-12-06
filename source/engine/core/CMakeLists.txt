

# Set the project name
project (core)

# Add a library with the above sources
# add_library(${PROJECT_NAME} src/vector.cpp)
# add_library(engine::core ALIAS ${PROJECT_NAME})

add_library(${PROJECT_NAME} SHARED 
    src/dll.cpp
    src/vector.cpp
    )
add_library(engine::core ALIAS ${PROJECT_NAME})

GENERATE_EXPORT_HEADER( ${PROJECT_NAME}
             BASE_NAME ${PROJECT_NAME}
             EXPORT_MACRO_NAME ${PROJECT_NAME}_EXPORT
             EXPORT_FILE_NAME ${PROJECT_NAME}_Export.h
             STATIC_DEFINE ${PROJECT_NAME}_BUILT_AS_STATIC
)

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR} 
)

target_link_libraries( ${PROJECT_NAME}
${LUA_LIBRARIES}
${FREETYPE_LIBRARIES})
