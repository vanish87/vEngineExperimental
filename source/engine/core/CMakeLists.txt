

# Set the project name
project (core)

# Add a library with the above sources
add_library(${PROJECT_NAME} src/vector.cpp)
add_library(engine::core ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries( ${PROJECT_NAME}
${LUA_LIBRARIES}
${FREETYPE_LIBRARIES})
