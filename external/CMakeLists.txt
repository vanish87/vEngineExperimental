cmake_minimum_required(VERSION 3.13)

IF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  SET(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/build CACHE PATH "set external" FORCE)
ENDIF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

set(CMAKE_DEBUG_POSTFIX d)

if(WIN32)
  add_subdirectory(assimp)
endif(WIN32)

# add_subdirectory(zlib)
add_subdirectory(freetype2)
add_subdirectory(lua)
add_subdirectory(glfw)

#add_subdirectory(tinyxml2)

#build directxtex and FX11 mannully
#add_subdirectory(directxtex)
#add_subdirectory(FX11)

#use pre-compiled lib for now
#add_subdirectory(ManualBuild)
