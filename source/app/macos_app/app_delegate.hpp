#ifndef _APP_MACOS_APP_APP_DELEGATE_HPP
#define _APP_MACOS_APP_APP_DELEGATE_HPP

#include <apple/target_define.hpp>

#if defined(VENGINE_PLATFORM_TARGET_DARWIN)
//system header, not the metal-cpp header
#import <AppKit/AppKit.h>
#define PlatformAppDelegate NSObject<NSApplicationDelegate>
#else
#import <UIKit/UIKit.h>
#define PlatformAppDelegate UIResponder<UIApplicationDelegate>
#endif

@interface AppDelegate : PlatformAppDelegate

#if defined(VENGINE_PLATFORM_TARGET_IOS)
@property (strong, nonatomic) UIWindow *window;
#endif

@end


#endif /* _APP_MACOS_APP_APP_DELEGATE_HPP */
