project(test_example)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

add_subdirectory(external/googletest)
enable_testing()

include_directories(${PROJECT_SOURCE_DIR}/external/googletest/googletest/include)

# Create the executable
add_executable(${PROJECT_NAME} 
	test_vector.cpp
	test_main.cpp
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