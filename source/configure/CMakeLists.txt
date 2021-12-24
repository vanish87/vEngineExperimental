# Meta information about the project
set(META_PROJECT_NAME        "vEngine")
set(META_PROJECT_DESCRIPTION "CMake Template")
set(META_AUTHOR_ORGANIZATION "")
set(META_AUTHOR_DOMAIN       "https://github.com/vanish87/")
set(META_AUTHOR_MAINTAINER   "vanish87@test.com")
set(META_VERSION_MAJOR       "2")
set(META_VERSION_MINOR       "1")
set(META_VERSION_PATCH       "0")
set(META_VERSION_REVISION    "${GIT_REV}")
set(META_VERSION             "${META_VERSION_MAJOR}.${META_VERSION_MINOR}.${META_VERSION_PATCH}")
set(META_NAME_VERSION        "${META_PROJECT_NAME} v${META_VERSION} (${META_VERSION_REVISION})")
set(META_CMAKE_INIT_SHA      "${GIT_REV}")

string(MAKE_C_IDENTIFIER ${META_PROJECT_NAME} META_PROJECT_ID)
string(TOUPPER ${META_PROJECT_ID} META_PROJECT_ID)

configure_file(version.hpp.in ${CONFIGURE_INCLUDE}/version.hpp)
configure_file(compiler_setting.hpp.in ${CONFIGURE_INCLUDE}/compiler_setting.hpp)

