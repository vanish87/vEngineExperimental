#import "AppDelegate.hpp"

@implementation AppDelegate

#if defined(APP_PLATFORM_TARGET_DARWIN)
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender 
{
    return YES;
}
#else
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions 
{
	[self performSelector:@selector(app_main_loop) withObject:nil afterDelay:0.0];
    return YES;
}
 - (void)app_main_loop
 {
	 //Trigger app main loop here
 }
#endif

@end
