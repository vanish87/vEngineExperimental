#ifndef _VENGINE_CORE_APP_MAIN_HPP
#define _VENGINE_CORE_APP_MAIN_HPP

#import <vengine/core/apple/define.hpp>

#if defined(APP_PLATFORM_TARGET_DARWIN)
#import <Cocoa/Cocoa.h>
#else
#import <Availability.h>
#import <UIKit/UIKit.h>
#import <vengine/core/apple/app_delegate.hpp>
#endif

#if defined(APP_PLATFORM_TARGET_DARWIN)
int main(int argc, const char * argv[])
{
    return NSApplicationMain(argc, argv);
}
#else
int main(int argc, char * argv[])
{
    @autoreleasepool {
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
}
#endif

void AppleAppMain(void* wnd);

#endif /* _VENGINE_CORE_APP_MAIN_HPP */
