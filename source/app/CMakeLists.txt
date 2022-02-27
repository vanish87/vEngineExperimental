if(WIN32)
	add_subdirectory(d3d11_app)
endif(WIN32)
	
add_subdirectory(opengl_app)
add_subdirectory(example_app)

if(APPLE)
	add_subdirectory(macos_app)
endif()