
if(WIN32)
	set(SHARED_LIB_PREFIX "./")
	set(SHARED_LIB_EXT ".dll")
elseif(APPLE)
	set(SHARED_LIB_PREFIX "./lib")
	set(SHARED_LIB_EXT ".dylib")
else()
	set(SHARED_LIB_PREFIX "./lib")
	set(SHARED_LIB_EXT ".so")
endif()

set(SHARED_LIB_DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

string(MAKE_C_IDENTIFIER ${META_PROJECT_NAME} META_PROJECT_ID)
string(TOUPPER ${META_PROJECT_ID} META_PROJECT_ID)

configure_file(version.hpp.in ${CONFIGURE_INCLUDE}/version.hpp)
configure_file(compiler_setting.hpp.in ${CONFIGURE_INCLUDE}/compiler_setting.hpp)
configure_file(macros.hpp.in ${CONFIGURE_INCLUDE}/macros.hpp)
configure_file(defines.hpp.in ${CONFIGURE_INCLUDE}/defines.hpp)

