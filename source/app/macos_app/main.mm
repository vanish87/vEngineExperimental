
#import <apple/target_define.hpp>

#if defined(VENGINE_PLATFORM_TARGET_DARWIN)
#import <Cocoa/Cocoa.h>
#else
#import <Availability.h>
#import <UIKit/UIKit.h>
#import "app_delegate.hpp"
#endif

#import "apple_app.hpp"
#import <vengine/core/context.hpp>
#import <vengine/core/configure.hpp>
#import <vengine/rendering/render_engine.hpp>

#if defined(VENGINE_PLATFORM_TARGET_DARWIN)
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


void AppleAppMain()
{
    std::cout << "Version " + std::string(Version) << std::endl;

    vEngine::Core::Configure configure;
    configure.graphics_configure.width = 1280;
    configure.graphics_configure.height = 720;
    configure.graphics_configure.render_plugin_name = "metal_rendering_plugin";

    vEngine::Core::Context::GetInstance().SetConfigure(configure);
    auto& re = vEngine::Core::Context::GetInstance().GetRenderEngine();
    // re.PrintInfo();

    auto app = std::make_shared<AppleApp::ExampleApp>();
    app->Run();
}
