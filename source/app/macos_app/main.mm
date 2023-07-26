
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
int main(const int argc, const char * argv[])
{
    return NSApplicationMain(argc, argv);
}
#else
int main(const int argc, char * argv[])
{
    @autoreleasepool {
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
}
#endif

std::shared_ptr<AppleApp::ExampleApp> app;

void AppleAppMain(const int argc, const char * argv[])
{
    std::cout << "Version " + std::string(Version) << std::endl;

    vEngine::Core::Configure configure;
    configure.graphics_configure.width = 1280;
    configure.graphics_configure.height = 720;
    configure.graphics_configure.render_plugin_name = "metal_rendering_plugin";
    configure.ImportArgs(argc, argv);

    vEngine::Core::Context::GetInstance().SetConfigure(configure);
    auto& re = vEngine::Core::Context::GetInstance().GetRenderEngine();
    // re.PrintInfo();

    app = std::make_shared<AppleApp::ExampleApp>();
    app->RunAsync();
}
