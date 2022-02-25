#ifndef _APP_MACOS_APP_APPVIEWCONTROLLER_HPP
#define _APP_MACOS_APP_APPVIEWCONTROLLER_HPP

#import <vengine/core/apple/define.hpp>

#if defined(APP_PLATFORM_TARGET_DARWIN)
#import <AppKit/AppKit.h>
#define PlatformViewController NSViewController
#else
#import  <UIKit/UIKit.h>
#define PlatformViewController UIViewController
#endif

#import <MetalKit/MetalKit.h>

// The view controller
@interface AppViewController : PlatformViewController <MTKViewDelegate>

@end


#endif /* _APP_MACOS_APP_APPVIEWCONTROLLER_HPP */
