
# FX11_FOUND
# FX11_INCLUDE_DIR
# FX11_LIBRARY_RELEASE
# FX11_LIBRARY_DEBUG
# FX11_LIBRARIES
# FX11_BINARY (win32 only)

include(FindPackageHandleStandardArgs)

find_path(FX11_INCLUDE_DIR FX11/d3dx11effect.h

    PATHS
    $ENV{FX11_DIR}
    $ENV{PROGRAMFILES}/Assimp
    /usr
    /usr/local
    /sw
    /opt/local
	${EXTERNAL_PRE_BUILD_DIR}

    PATH_SUFFIXES
    /include

    DOC "The directory where FX11/Importer.hpp etc. resides")

if(MSVC AND X64)
    set(FX11_PF "64")
else()
    set(FX11_PF "86")
endif()

find_library(FX11_LIBRARY_RELEASE NAMES Effects11
    
    HINTS
    ${FX11_INCLUDE_DIR}/..
    
    PATHS
    $ENV{FX11_DIR}
    /usr
    /usr/local
    /sw
    /opt/local

    PATH_SUFFIXES
    /lib
    /lib${FX11_PF}
    /build/code
    /build-debug/code

    DOC "The Assimp library (release)")

find_library(FX11_LIBRARY_DEBUG NAMES Effects11d
    
    HINTS
    ${FX11_INCLUDE_DIR}/..

    PATHS
    $ENV{FX11_DIR}
    /usr
    /usr/local
    /sw
    /opt/local

    PATH_SUFFIXES
    /lib
    /lib${FX11_PF}
    /build/code
    /build-debug/code

    DOC "The Assimp library (debug)")

set(FX11_LIBRARIES "")
if(FX11_LIBRARY_RELEASE AND FX11_LIBRARY_DEBUG)
    set(FX11_LIBRARIES 
        optimized   ${FX11_LIBRARY_RELEASE}
        debug       ${FX11_LIBRARY_DEBUG})
elseif(FX11_LIBRARY_RELEASE)
    set(FX11_LIBRARIES ${FX11_LIBRARY_RELEASE})
elseif(FX11_LIBRARY_DEBUG)
    set(FX11_LIBRARIES ${FX11_LIBRARY_DEBUG})
endif()

if(WIN32)

    find_file(FX11_BINARY NAMES FX11.dll "FX11${FX11_PF}.dll"

        HINTS
        ${FX11_INCLUDE_DIR}/..
        
        PATHS
        $ENV{FX11_DIR}

        PATH_SUFFIXES
        /bin
        /bin${FX11_PF}

        DOC "The Assimp binary")

endif()

find_package_handle_standard_args(FX11 DEFAULT_MSG FX11_LIBRARIES FX11_INCLUDE_DIR)
mark_as_advanced(FX11_FOUND FX11_INCLUDE_DIR FX11_LIBRARIES)
