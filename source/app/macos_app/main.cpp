
#include <engine.hpp>
#include <version.hpp>
#include <vengine/core/application_macos.hpp>
#include <vengine/core/context.hpp>

int main( int argc, const char* argv[] )
{
    std::cout << "Version " + std::string(Version) << std::endl;

    vEngine::Core::Configure configure;
    configure.graphics_configure.width = 1280;
    configure.graphics_configure.height = 720;
    configure.graphics_configure.render_plugin_name = "metal_rendering_plugin";
    configure.argc = argc;
    //configure.argv = argv;

    vEngine::Core::Context::GetInstance().SetConfigure(configure);
    auto& re = vEngine::Core::Context::GetInstance().GetRenderEngine();
    // re.PrintInfo();

    auto app = std::make_shared<vEngine::Core::ApplicationMacOS>();
    app->Run();

    // NS::AutoreleasePool* pAutoreleasePool = NS::AutoreleasePool::alloc()->init();

    // MyAppDelegate del;

    // #if defined(APP_PLATFORM_TARGET_DARWIN)
    // NS::Application* pSharedApplication = NS::Application::sharedApplication();
    // pSharedApplication->setDelegate(&del);
    // pSharedApplication->run();
    // #else
    // UI::ApplicationMain(argc, argv, &del);
    // #endif

    // pAutoreleasePool->release();

    return 0;
}

void AppleAppMain(void* wnd)
{
}
