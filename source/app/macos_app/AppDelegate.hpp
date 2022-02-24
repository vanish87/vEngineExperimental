
#import "define.hpp"

#if defined(APP_PLATFORM_TARGET_DARWIN)
#import <AppKit/AppKit.h>
#define PlatformAppDelegate NSObject<NSApplicationDelegate>
#else
#import <UIKit/UIKit.h>
#define PlatformAppDelegate UIResponder <UIApplicationDelegate>
#endif

@interface AppDelegate : PlatformAppDelegate

#if defined(APP_PLATFORM_TARGET_IOS)
@property (strong, nonatomic) UIWindow *window;
#endif

@end
