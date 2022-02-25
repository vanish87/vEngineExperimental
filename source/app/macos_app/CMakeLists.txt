
set(APP_BUNDLE_IDENTIFIER "com.vanish87.my-ios-app") 
set(CMAKE_XCODE_ATTRIBUTE_DEVELOPMENT_TEAM KH98AQQ5YQ)
# set(CMAKE_CXX_STANDARD 17)

# if(BUILD_IOS)
#   set(CMAKE_SYSTEM_NAME iOS)
#   set(CMAKE_OSX_SYSROOT iphoneos)
# endif()

message("${CMAKE_OSX_SYSROOT}")
message("${BUILD_IOS}")

set(COMMON_HEADER_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/apple_app.hpp
)

set(COMMON_SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/main.mm
)

if(BUILD_IOS)
  add_subdirectory(ios)
else()
  add_subdirectory(macos)
endif()


# set(RESOURCES
#   iOS/Main.storyboard
#   # LaunchScreen.storyboard
# )

# add_executable(${PROJECT_NAME} 
# 	MACOSX_BUNDLE
# 	${COMMON_HEADER_FILES}
# 	${COMMON_SOURCE_FILES}
# 	${RESOURCES}
# )

# find_library(UIKIT_LIB UIKit)
# find_library(FOUNDATION_LIB Foundation)

# # target_link_libraries(${PROJECT_NAME}
# #     "-framework UIKit"
# # )

# target_link_libraries(${PROJECT_NAME} ${FOUNDATION_LIB})
# target_link_libraries(${PROJECT_NAME} ${UIKIT_LIB})
# target_link_libraries(${PROJECT_NAME} engine::render)

# target_include_directories(${PROJECT_NAME}
#     PUBLIC ${metal_cpp_framework_SOURCE_DIR}
# )

# set_target_properties(${PROJECT_NAME} PROPERTIES
#                     #   XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT "dwarf-with-dsym"
#                     #   XCODE_ATTRIBUTE_GCC_PREFIX_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/Prefix.pch"
#                         RESOURCE "${RESOURCES}"
#                     #   XCODE_ATTRIBUTE_GCC_PRECOMPILE_PREFIX_HEADER "YES"
#                     #   XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET ${DEPLOYMENT_TARGET}
#                     #   XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY ${CODE_SIGN_IDENTITY}
#                     #   XCODE_ATTRIBUTE_DEVELOPMENT_TEAM ${DEVELOPMENT_TEAM_ID}
#                     #   XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY ${DEVICE_FAMILY}
#                         MACOSX_BUNDLE_GUI_IDENTIFIER ${APP_BUNDLE_IDENTIFIER}
#                         MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/iOS/plist.in
#                     #   XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC YES
#                     #   XCODE_ATTRIBUTE_COMBINE_HIDPI_IMAGES NO
#                     #   XCODE_ATTRIBUTE_INSTALL_PATH "$(LOCAL_APPS_DIR)"
#                     #   XCODE_ATTRIBUTE_ENABLE_TESTABILITY YES
#                     #   XCODE_ATTRIBUTE_GCC_SYMBOLS_PRIVATE_EXTERN YES
# )
