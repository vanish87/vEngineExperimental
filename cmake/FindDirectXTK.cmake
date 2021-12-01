
# DIRECTXTK
# DIRECTXTK_INCLUDE_DIR
# DIRECTXTK_LIBRARY_RELEASE
# DIRECTXTK_LIBRARY_DEBUG
# DIRECTXTK_LIBRARIES
# DIRECTXTK_BINARY (win32 only)

include(FindPackageHandleStandardArgs)

find_path(DIRECTXTK_INCLUDE_DIR 
	NAMES 
	DirectXTK/Audio.h

    PATHS
    $ENV{DIRECTXTK_DIR}
    $ENV{PROGRAMFILES}/Assimp
    /usr
    /usr/local
    /sw
    /opt/local
	${EXTERNAL_PRE_BUILD_DIR}

    PATH_SUFFIXES
    /include

    DOC "The directory where assimp/Importer.hpp etc. resides")

if(MSVC AND X64)
    set(DIRECTXTK_PF "64")
else()
    set(DIRECTXTK_PF "86")
endif()

find_library(DIRECTXTK_LIBRARY_RELEASE NAMES DirectXTK
    
    HINTS
    ${DIRECTXTK_INCLUDE_DIR}/..
    
    PATHS
    $ENV{DIRECTXTK_DIR}
    /usr
    /usr/local
    /sw
    /opt/local

    PATH_SUFFIXES
    /lib
    /lib${DIRECTXTK_PF}
    /build/code
    /build-debug/code

    DOC "The Assimp library (release)")

find_library(DIRECTXTK_LIBRARY_DEBUG NAMES DirectXTKd
    
    HINTS
    ${DIRECTXTK_INCLUDE_DIR}/..

    PATHS
    $ENV{DIRECTXTK_DIR}
    /usr
    /usr/local
    /sw
    /opt/local

    PATH_SUFFIXES
    /lib
    /lib${DIRECTXTK_PF}
    /build/code
    /build-debug/code

    DOC "The Assimp library (debug)")

set(DIRECTXTK_LIBRARIES "")
if(DIRECTXTK_LIBRARY_RELEASE AND DIRECTXTK_LIBRARY_DEBUG)
    set(DIRECTXTK_LIBRARIES 
        optimized   ${DIRECTXTK_LIBRARY_RELEASE}
        debug       ${DIRECTXTK_LIBRARY_DEBUG})
elseif(DIRECTXTK_LIBRARY_RELEASE)
    set(DIRECTXTK_LIBRARIES ${DIRECTXTK_LIBRARY_RELEASE})
elseif(DIRECTXTK_LIBRARY_DEBUG)
    set(DIRECTXTK_LIBRARIES ${DIRECTXTK_LIBRARY_DEBUG})
endif()

if(WIN32)

    find_file(DIRECTXTK_BINARY NAMES assimp.dll "assimp${DIRECTXTK_PF}.dll"

        HINTS
        ${DIRECTXTK_INCLUDE_DIR}/..
        
        PATHS
        $ENV{DIRECTXTK_DIR}

        PATH_SUFFIXES
        /bin
        /bin${DIRECTXTK_PF}

        DOC "The Assimp binary")

endif()

find_package_handle_standard_args(DIRECTXTK DEFAULT_MSG DIRECTXTK_LIBRARIES DIRECTXTK_INCLUDE_DIR)
mark_as_advanced(DIRECTXTK DIRECTXTK_INCLUDE_DIR DIRECTXTK_LIBRARIES)
