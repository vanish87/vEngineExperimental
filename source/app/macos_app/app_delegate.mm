#import "app_delegate.hpp"
#import "app_main.hpp"

@implementation AppDelegate

#if defined(VENGINE_PLATFORM_TARGET_DARWIN)
- (void)applicationDidFinishLaunching:(NSNotification *)notification
{
    AppleAppMain(0, nullptr);
}
#else
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions 
{
//    [self performSelectorInBackground:@selector(app_main_loop) withObject:nil afterDelay:0.0];
//     dispatch_async(dispatch_get_main_queue(), ^{
//     });
    
    
//    NSString *nsBunldePath = [[NSString alloc] initWithUTF8String:"bunny.obj"];
//    NSURL *modelFileURL = [[NSBundle mainBundle] URLForResource:nsBunldePath withExtension:nil];
//    NSString *fileContents = [[NSString alloc] initWithContentsOfURL:modelFileURL];
        
    AppleAppMain(0, nullptr);
    return YES;
}
#endif

@end
