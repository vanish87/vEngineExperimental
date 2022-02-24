#ifndef _APPVIEWCONTROLLER_HPP
#define _APPVIEWCONTROLLER_HPP

#pragma once

#import "define.hpp"

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


#endif /* _APPVIEWCONTROLLER_HPP */
