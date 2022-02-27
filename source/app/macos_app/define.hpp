#ifndef _APP_MACOS_APP_DEFINE_HPP
#define _APP_MACOS_APP_DEFINE_HPP

#include <TargetConditionals.h>

//build system is darwin
#define APP_PLATFORM_BUILD_DARWIN

//target(running) system is darwin or iOS/Simulator
#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
 	#define APP_PLATFORM_TARGET_IOS
#else
	#define APP_PLATFORM_TARGET_DARWIN
#endif

//only use this for simulator check
#if TARGET_IPHONE_SIMULATOR
	#define APP_PLATFORM_TARGET_IOS_SIMULATOR
#endif

#endif /* _APP_MACOS_APP_DEFINE_HPP */
