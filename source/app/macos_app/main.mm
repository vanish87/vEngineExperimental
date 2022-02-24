#import "define.hpp"

#if defined(APP_PLATFORM_TARGET_DARWIN)
#import <Cocoa/Cocoa.h>
#else
#import <Availability.h>
#import <UIKit/UIKit.h>
#import "AppDelegate.hpp"
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
