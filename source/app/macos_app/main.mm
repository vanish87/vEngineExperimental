#import "apple_app.hpp"
#import <vengine/core/apple/app_main.hpp>

void AppleAppMain(void* wnd)
{
    std::cout << "Version " + std::string(Version) << std::endl;

    Configure configure;
    configure.graphics_configure.width = 1280;
    configure.graphics_configure.height = 720;
    configure.graphics_configure.render_plugin_name = "metal_rendering_plugin";

    Context::GetInstance().ConfigureWith(configure);

    AppleApp::ExampleApp app;
    app.Init(wnd);
    app.Run();
}