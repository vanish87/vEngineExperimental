#import "apple_app.hpp"
#import <vengine/core/apple/app_main.hpp>
#import <vengine/core/context.hpp>
#import <vengine/core/configure.hpp>

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