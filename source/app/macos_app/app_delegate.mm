#import "app_delegate.hpp"
#import "app_main.hpp"

@implementation AppDelegate

#if defined(VENGINE_PLATFORM_TARGET_DARWIN)
- (void)applicationDidFinishLaunching:(NSNotification *)notification
{
    dispatch_async(dispatch_get_main_queue(), ^{
        AppleAppMain();
    });
//    NSLog(@"applicationDidFinishLaunching");
//    [self performSelectorInBackground:@selector(app_main_loop) withObject:nil afterDelay:0.0];

}
#else
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions 
{
//    NSLog(@"didFinishLaunchingWithOptions");
    //NSLog(@"%@",NSStringFromCGRect(self.window.bounds));
//    [self performSelectorInBackground:@selector(app_main_loop) withObject:nil afterDelay:0.0];
    dispatch_async(dispatch_get_main_queue(), ^{
        AppleAppMain();
    });
    return YES;
}
#endif

@end
