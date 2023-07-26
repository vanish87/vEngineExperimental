#ifndef _INCLUDE_APPLE_TARGET_DEFINE_HPP
#define _INCLUDE_APPLE_TARGET_DEFINE_HPP

#if VENGINE_PLATFORM_APPLE

    #include <TargetConditionals.h>

    // build system is darwin
    #define VENGINE_PLATFORM_HOST_DARWIN

    // target(running) system is darwin or iOS/Simulator
    #if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
        #define VENGINE_PLATFORM_TARGET_IOS
    #else
        #define VENGINE_PLATFORM_TARGET_DARWIN
    #endif

    // only use this for simulator check
    #if TARGET_IPHONE_SIMULATOR
        #define APPLE_PLATFORM_TARGET_IOS_SIMULATOR
    #endif

#endif

#endif /* _INCLUDE_APPLE_TARGET_DEFINE_HPP */
