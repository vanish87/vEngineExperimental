if(WIN32)
	add_subdirectory(d3d11)
endif()

if(UNIX)
	if(APPLE)
		add_subdirectory(metal)
	else()
		add_subdirectory(opengl)
	endif()
endif()

add_subdirectory(empty)