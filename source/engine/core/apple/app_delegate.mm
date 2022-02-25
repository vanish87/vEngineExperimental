#import "app_delegate.hpp"

@implementation AppDelegate

#if defined(APP_PLATFORM_TARGET_DARWIN)
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender 
{
    return YES;
}
#else
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions 
{
    return YES;
}
#endif

@end
