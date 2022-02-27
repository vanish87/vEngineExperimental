
#import "define.hpp"

#if defined(APP_PLATFORM_TARGET_DARWIN)
#import <Cocoa/Cocoa.h>
#else
#import <Availability.h>
#import <UIKit/UIKit.h>
#import <vengine/core/apple/app_delegate.hpp>
#endif

#import "apple_app.hpp"
#import "app_main.hpp"
#import <vengine/core/context.hpp>
#import <vengine/core/configure.hpp>

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


void AppleAppMain(void* wnd)
{
    std::cout << "Version " + std::string(Version) << std::endl;

    vEngine::Core::Configure configure;
    configure.graphics_configure.width = 1280;
    configure.graphics_configure.height = 720;
    configure.graphics_configure.render_plugin_name = "metal_rendering_plugin";

    vEngine::Core::Context::GetInstance().ConfigureWith(configure);

    AppleApp::ExampleApp app;
    app.Init(wnd);
    app.Run();
}