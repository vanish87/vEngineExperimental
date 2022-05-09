
include(FindPackageHandleStandardArgs)


if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(ASSIMP_ARCHITECTURE "64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
	set(ASSIMP_ARCHITECTURE "32")
endif(CMAKE_SIZEOF_VOID_P EQUAL 8)

set(ASSIMP_ROOT_DIR ${EXTERNAL_BUILD_DIR})
if(WIN32)

	# message(STATUS "ASSIMP_ROOT_DIR= ${ASSIMP_ROOT_DIR}")

	# Find path of each library
	find_path(ASSIMP_INCLUDE_DIR
		NAMES
			assimp/anim.h
		HINTS
			${ASSIMP_ROOT_DIR}/include
	)

	# message(STATUS "ASSIMP_INCLUDE_DIR= ${ASSIMP_INCLUDE_DIR}")

	if( MSVC )
		# in order to prevent DLL hell, each of the DLLs have to be suffixed with the major version and msvc prefix
		# CMake 3.12 added a variable for this
		set(ASSIMP_MSVC_VERSION "vc${MSVC_TOOLSET_VERSION}")
	endif()

	find_path(ASSIMP_LIBRARY_DIR
		NAMES
			assimp-${ASSIMP_MSVC_VERSION}-mt.lib
		HINTS
			${ASSIMP_ROOT_DIR}/lib${ASSIMP_ARCHITECTURE}
			${ASSIMP_ROOT_DIR}/lib
	)
	
	find_library(ASSIMP_LIBRARY_RELEASE				assimp-${ASSIMP_MSVC_VERSION}-mt.lib 			PATHS ${ASSIMP_LIBRARY_DIR})
	find_library(ASSIMP_LIBRARY_DEBUG				assimp-${ASSIMP_MSVC_VERSION}-mtd.lib			PATHS ${ASSIMP_LIBRARY_DIR})
	
	set(ASSIMP_LIBRARY 
		optimized 	${ASSIMP_LIBRARY_RELEASE}
		debug		${ASSIMP_LIBRARY_DEBUG}
	)
	
	set(ASSIMP_LIBRARIES ${ASSIMP_LIBRARY} )

	FUNCTION(ASSIMP_COPY_BINARIES TargetDirectory)
		ADD_CUSTOM_TARGET(AssimpCopyBinaries
			COMMAND ${CMAKE_COMMAND} -E copy ${ASSIMP_ROOT_DIR}/bin${ASSIMP_ARCHITECTURE}/assimp-${ASSIMP_MSVC_VERSION}-mtd.dll 	${TargetDirectory}/Debug/assimp-${ASSIMP_MSVC_VERSION}-mtd.dll
			COMMAND ${CMAKE_COMMAND} -E copy ${ASSIMP_ROOT_DIR}/bin${ASSIMP_ARCHITECTURE}/assimp-${ASSIMP_MSVC_VERSION}-mt.dll 		${TargetDirectory}/Release/assimp-${ASSIMP_MSVC_VERSION}-mt.dll
		COMMENT "Copying Assimp binaries to '${TargetDirectory}'"
		VERBATIM)
	ENDFUNCTION(ASSIMP_COPY_BINARIES)
	
	
else(WIN32)

	find_path(ASSIMP_INCLUDE_DIR
		NAMES
			assimp/anim.h
		HINTS
			${ASSIMP_ROOT_DIR}/include
	)

	set(ASSIMP_LIB_EXT "so")

	if(APPLE)
		set(ASSIMP_LIB_EXT "dylib")
	endif(APPLE)

	find_path(ASSIMP_LIBRARY_DIR
		NAMES
			libassimp.${ASSIMP_LIB_EXT}
		HINTS
			${ASSIMP_ROOT_DIR}/lib
	)

	find_library(ASSIMP_LIBRARY_DEBUG				libassimpd.${ASSIMP_LIB_EXT}			PATHS ${ASSIMP_LIBRARY_DIR})
	find_library(ASSIMP_LIBRARY_RELEASE				libassimp.${ASSIMP_LIB_EXT} 			PATHS ${ASSIMP_LIBRARY_DIR})

	set(ASSIMP_LIBRARY 
		optimized 	${ASSIMP_LIBRARY_RELEASE}
		debug		${ASSIMP_LIBRARY_DEBUG}
	)

	set(ASSIMP_LIBRARIES ${ASSIMP_LIBRARY})

	if (ASSIMP_INCLUDE_DIR AND ASSIMP_LIBRARIES)
		SET(ASSIMP_FOUND TRUE)
	ENDIF (ASSIMP_INCLUDE_DIR AND ASSIMP_LIBRARIES)

	if (ASSIMP_FOUND)
	  if (NOT ASSIMPND_QUIETLY)
		message(STATUS "Found asset importer library: ${assimp_LIBRARIES}")
	  endif (NOT ASSIMP_FIND_QUIETLY)
	else (ASSIMP_FOUND)
	#   if (assimp_FIND_REQUIRED)
	# 	message(FATAL_ERROR "Could not find asset importer library")
	#   endif (assimp_FIND_REQUIRED)
	endif (ASSIMP_FOUND)
	
endif(WIN32)


find_package_handle_standard_args(ASSIMP DEFAULT_MSG ASSIMP_LIBRARIES ASSIMP_INCLUDE_DIR)
