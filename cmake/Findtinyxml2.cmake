
# TINYXML2_FOUND
# TINYXML2_INCLUDE_DIR
# TINYXML2_LIBRARY_RELEASE
# TINYXML2_LIBRARY_DEBUG
# TINYXML2_LIBRARIES
# TINYXML2_BINARY (win32 only)

include(FindPackageHandleStandardArgs)

find_path(TINYXML2_INCLUDE_DIR tinyxml2.h

    PATHS
    $ENV{TINYXML2_DIR}
    $ENV{PROGRAMFILES}/TINYXML2
    /usr
    /usr/local
    /sw
    /opt/local
	${EXTERNAL_BUILD_DIR}

    PATH_SUFFIXES
    /include

    DOC "The directory where TINYXML2/Importer.hpp etc. resides")

if(MSVC AND X64)
    set(TINYXML2_PF "64")
else()
    set(TINYXML2_PF "86")
endif()

find_library(TINYXML2_LIBRARY_RELEASE NAMES TINYXML2
    
    HINTS
    ${TINYXML2_INCLUDE_DIR}/..
    
    PATHS
    $ENV{TINYXML2_DIR}
    /usr
    /usr/local
    /sw
    /opt/local

    PATH_SUFFIXES
    /lib
    /lib${TINYXML2_PF}
    /build/code
    /build-debug/code

    DOC "The TINYXML2 library (release)")

find_library(TINYXML2_LIBRARY_DEBUG NAMES TINYXML2d
    
    HINTS
    ${TINYXML2_INCLUDE_DIR}/..

    PATHS
    $ENV{TINYXML2_DIR}
    /usr
    /usr/local
    /sw
    /opt/local

    PATH_SUFFIXES
    /lib
    /lib${TINYXML2_PF}
    /build/code
    /build-debug/code

    DOC "The TINYXML2 library (debug)")

set(TINYXML2_LIBRARIES "")
if(TINYXML2_LIBRARY_RELEASE AND TINYXML2_LIBRARY_DEBUG)
    set(TINYXML2_LIBRARIES 
        optimized   ${TINYXML2_LIBRARY_RELEASE}
        debug       ${TINYXML2_LIBRARY_DEBUG})
elseif(TINYXML2_LIBRARY_RELEASE)
    set(TINYXML2_LIBRARIES ${TINYXML2_LIBRARY_RELEASE})
elseif(TINYXML2_LIBRARY_DEBUG)
    set(TINYXML2_LIBRARIES ${TINYXML2_LIBRARY_DEBUG})
endif()

if(WIN32)

    find_file(TINYXML2_BINARY NAMES TINYXML2.dll "TINYXML2${TINYXML2_PF}.dll"

        HINTS
        ${TINYXML2_INCLUDE_DIR}/..
        
        PATHS
        $ENV{TINYXML2_DIR}

        PATH_SUFFIXES
        /bin
        /bin${TINYXML2_PF}

        DOC "The TINYXML2 binary")

endif()

find_package_handle_standard_args(TINYXML2 DEFAULT_MSG TINYXML2_LIBRARIES TINYXML2_INCLUDE_DIR)
mark_as_advanced(TINYXML2_FOUND TINYXML2_INCLUDE_DIR TINYXML2_LIBRARIES)
