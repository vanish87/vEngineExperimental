
add_subdirectory(editor_plugin)

if(WIN32 AND MSVC)
	 add_subdirectory(wpf_editor)
endif()

