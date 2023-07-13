
#include <engine.hpp>
#include <version.hpp>
#include <vengine/core/application_ios.hpp>
#include <vengine/core/context.hpp>

int main( int argc, const char* argv[] )
{
    // NS::AutoreleasePool* pAutoreleasePool = NS::AutoreleasePool::alloc()->init();

    // MyAppDelegate del;
    // UI::ApplicationMain(argc, argv, &del);

    // pAutoreleasePool->release();
    std::cout << "Version " + std::string(Version) << std::endl;

    vEngine::Core::Configure configure;
    configure.graphics_configure.width = 1280;
    configure.graphics_configure.height = 720;
    configure.graphics_configure.render_plugin_name = "metal_rendering_plugin";

    vEngine::Core::Context::GetInstance().SetConfigure(configure);
    auto& re = vEngine::Core::Context::GetInstance().GetRenderEngine();
    // re.PrintInfo();

    auto app = std::make_shared<vEngine::Core::ApplicationIOS>();
    app->Run();

    return 0;
}

