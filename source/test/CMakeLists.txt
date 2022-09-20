project(test_example)

# if(MSVC)
# 	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
# 	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
# endif(MSVC)

if(NOT BUILD_SHARED_LIBS)
	set(gtest_force_shared_crt on)
endif()

add_subdirectory(external/googletest)
enable_testing()

include_directories(${PROJECT_SOURCE_DIR}/external/googletest/googletest/include)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} test_source)

# Create the executable
add_executable(${PROJECT_NAME} 
	${test_source}
)

# Link the static library from subproject1 using its alias sub::lib1
# Link the header only library from subproject2 using its alias sub::lib2
# This will cause the include directories for that target to be added to this project
target_link_libraries(${PROJECT_NAME}
    engine::core
	gtest
	gtest_main
)

add_test(test_all ${PROJECT_NAME})