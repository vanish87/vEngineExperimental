
# GLFW_FOUND
# GLFW_INCLUDE_DIR
# GLFW_LIBRARY_RELEASE
# GLFW_LIBRARY_DEBUG
# GLFW_LIBRARIES
# GLFW_BINARY (win32 only)

include(FindPackageHandleStandardArgs)

unset(GLFW_INCLUDE_DIR)

find_path(GLFW_INCLUDE_DIR GLFW/glfw3.h

    PATHS
    $ENV{GLFW_DIR}
    $ENV{PROGRAMFILES}/GLFW3
    /usr
    /usr/local
    /sw
    /opt/local	
    ${EXTERNAL_BUILD_DIR}
    
    PATH_SUFFIXES
    /include
    /include/GLFW
    
    DOC "The directory where GLFW/Importer.hpp etc. resides"
	)



message("GLFW_INCLUDE_DIR ${GLFW_INCLUDE_DIR}")
if(MSVC AND X64)
    set(GLFW_PF "64")
else()
    set(GLFW_PF "86")
endif()

if(WIN32)	
	set(GLFW_DLLPF "3dll")
endif()

find_library(GLFW_LIBRARY_RELEASE NAMES glfw${GLFW_DLLPF}
    
    HINTS
    ${GLFW_INCLUDE_DIR}/..
    
    PATHS
    $ENV{GLFW_DIR}
    /usr
    /usr/local
    /usr/lib/x86_64-linux-gnu
    /sw
    /opt/local

    PATH_SUFFIXES
    /lib
    /lib${GLFW_PF}
    /build/code
    /build-debug/code

    DOC "The GLFW library (release)")


# message("GLFW_LIBRARY_RELEASE ${GLFW_LIBRARY_RELEASE}")

find_library(GLFW_LIBRARY_DEBUG NAMES glfw3ddll
    
    HINTS
    ${GLFW_INCLUDE_DIR}/..

    PATHS
    $ENV{GLFW_DIR}
    /usr
    /usr/local
    /sw
    /opt/local

    PATH_SUFFIXES
    /lib
    /lib${GLFW_PF}
    /build/code
    /build-debug/code

    DOC "The GLFW library (debug)")

set(GLFW_LIBRARIES "")
if(GLFW_LIBRARY_RELEASE AND GLFW_LIBRARY_DEBUG)
    set(GLFW_LIBRARIES 
        optimized   ${GLFW_LIBRARY_RELEASE}
        debug       ${GLFW_LIBRARY_DEBUG})
elseif(GLFW_LIBRARY_RELEASE)
    set(GLFW_LIBRARIES ${GLFW_LIBRARY_RELEASE})
elseif(GLFW_LIBRARY_DEBUG)
    set(GLFW_LIBRARIES ${GLFW_LIBRARY_DEBUG})
endif()

if(WIN32)

    find_file(GLFW_BINARY NAMES GLFW3.dll "GLFW3${GLFW_PF}.dll"

        HINTS
        ${GLFW_INCLUDE_DIR}/..
        
        PATHS
        $ENV{GLFW_DIR}

        PATH_SUFFIXES
        /bin
        /bin${GLFW_PF}

        DOC "The GLFW binary")

endif()

find_package_handle_standard_args(GLFW DEFAULT_MSG GLFW_LIBRARIES GLFW_INCLUDE_DIR)
mark_as_advanced(GLFW_FOUND GLFW_INCLUDE_DIR GLFW_LIBRARIES)
