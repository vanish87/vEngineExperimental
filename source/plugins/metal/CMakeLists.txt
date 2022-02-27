
project(metal_rendering_plugin)

# dynamic link is not working for ios
# lib build and link in static lib
# framework is lagacy code
set(METAL_AS_FRAMEWORK OFF)

# header only lib
# add_library(${PROJECT_NAME} INTERFACE)
# add_library(engine::metal_cpp ALIAS ${PROJECT_NAME})
# set(single_header_file_dir ${CMAKE_CURRENT_SOURCE_DIR}/SingleHeader/include)
# target_include_directories(${PROJECT_NAME} INTERFACE ${single_header_file_dir})

# metal.cpp contains implementation
# compiled as static/dynamic lib
add_library(${PROJECT_NAME} 
	src/metal.cpp
	src/metal_render_engine.cpp
	)
add_library(engine::metal_rendering_plugin ALIAS ${PROJECT_NAME})

# find_library(FOUNDATION_LIB Foundation)
# find_library(METAL_LIB Metal)
# target_link_libraries(${PROJECT_NAME} ${FOUNDATION_LIB})
# target_link_libraries(${PROJECT_NAME} ${METAL_LIB})

target_link_libraries(${PROJECT_NAME} "-framework Foundation")
target_link_libraries(${PROJECT_NAME} "-framework Metal")

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${vengine_SOURCE_DIR}/include
)

# target_link_libraries( ${PROJECT_NAME}
#     engine::core
# )

if(METAL_AS_FRAMEWORK)
  set_target_properties(${PROJECT_NAME} PROPERTIES
    FRAMEWORK TRUE
    # https://developer.apple.com/library/archive/documentation/MacOSX/Conceptual/BPFrameworks/Concepts/VersionInformation.html
    # as Major verison
    FRAMEWORK_VERSION A
    MACOSX_FRAMEWORK_IDENTIFIER com.cmake.dynamicFramework
    MACOSX_FRAMEWORK_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/framework.plist.in
    # "current version" in semantic format in Mach-O binary file
    VERSION 16.4.0
    # "compatibility version" in semantic format in Mach-O binary file
    SOVERSION 1.0.0
    PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/render.h
    # XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer"
  )
endif()
