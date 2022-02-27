#import "app_delegate.hpp"
#import "app_main.hpp"

@implementation AppDelegate

#if defined(APP_PLATFORM_TARGET_DARWIN)
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender 
{

    return YES;
}
#else
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions 
{
//    [self performSelectorInBackground:@selector(app_main_loop) withObject:nil afterDelay:0.0];
    return YES;
}
#endif
//- (void)app_main_loop: (void*) view
//{
//    //Trigger app main loop here
//    AppleAppMain(view);
//}
@end
