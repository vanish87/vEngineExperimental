
# FREETYPE_FOUND
# FREETYPE_INCLUDE_DIR
# FREETYPE_LIBRARY_RELEASE
# FREETYPE_LIBRARY_DEBUG
# FREETYPE_LIBRARIES
# FREETYPE_BINARY (win32 only)

include(FindPackageHandleStandardArgs)

find_path(FREETYPE_INCLUDE_DIR freetype/freetype.h

    PATHS
    # $ENV{FREETYPE_DIR}
    # $ENV{PROGRAMFILES}/freetype2
    # /usr
    # /usr/local
    # /sw
    # /opt/local	
    ${EXTERNAL_BUILD_DIR}
    
    PATH_SUFFIXES
    /include
    /include/freetype2
    
    DOC "The directory where FREETYPE/Importer.hpp etc. resides")


message(STATUS "FREETYPE_INCLUDE_DIR= ${FREETYPE_INCLUDE_DIR}")
if(MSVC AND X64)
    set(FREETYPE_PF "64")
else()
    set(FREETYPE_PF "86")
endif()

find_library(FREETYPE_LIBRARY_RELEASE NAMES freetype
    
    HINTS
    ${FREETYPE_INCLUDE_DIR}/../..
    
    PATHS
    # $ENV{FREETYPE_DIR}
    # /usr
    # /usr/local
    # /sw
    # /opt/local

    PATH_SUFFIXES
    /lib
    /lib${FREETYPE_PF}
    /build/code
    /build-debug/code

    DOC "The FREETYPE library (release)")

find_library(FREETYPE_LIBRARY_DEBUG NAMES freetyped
    
    HINTS
    ${FREETYPE_INCLUDE_DIR}/../..

    PATHS
    # $ENV{FREETYPE_DIR}
    # /usr
    # /usr/local
    # /sw
    # /opt/local

    PATH_SUFFIXES
    /lib
    /lib${FREETYPE_PF}
    /build/code
    /build-debug/code

    DOC "The FREETYPE library (debug)")

set(FREETYPE_LIBRARIES "")
if(FREETYPE_LIBRARY_RELEASE AND FREETYPE_LIBRARY_DEBUG)
    set(FREETYPE_LIBRARIES 
        optimized   ${FREETYPE_LIBRARY_RELEASE}
        debug       ${FREETYPE_LIBRARY_DEBUG})
elseif(FREETYPE_LIBRARY_RELEASE)
    set(FREETYPE_LIBRARIES ${FREETYPE_LIBRARY_RELEASE})
elseif(FREETYPE_LIBRARY_DEBUG)
    set(FREETYPE_LIBRARIES ${FREETYPE_LIBRARY_DEBUG})
endif()

if(WIN32)

    find_file(FREETYPE_BINARY NAMES freetype.dll "FREETYPE${FREETYPE_PF}.dll"

        HINTS
        ${FREETYPE_INCLUDE_DIR}/..
        
        PATHS
        # $ENV{FREETYPE_DIR}

        PATH_SUFFIXES
        /bin
        /bin${FREETYPE_PF}

        DOC "The FREETYPE binary")

endif()

find_package_handle_standard_args(FREETYPE DEFAULT_MSG FREETYPE_LIBRARIES FREETYPE_INCLUDE_DIR)
mark_as_advanced(FREETYPE_FOUND FREETYPE_INCLUDE_DIR FREETYPE_LIBRARIES)
