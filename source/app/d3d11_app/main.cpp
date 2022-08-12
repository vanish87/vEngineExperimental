#include <engine.hpp>
#include <version.hpp>
#include <vengine/core/application.hpp>
#include <vengine/core/constants.hpp>
#include <vengine/core/context.hpp>

using namespace vEngine::Core;

namespace Example
{
    class D3D11App : public Application
    {
    };
}  // namespace Example

int main(int argc, char* argv[])
{
    UNUSED_PARAMETER(argc);
    UNUSED_PARAMETER(argv);

    std::cout << "Version " + std::string(Version) << std::endl;

    Configure configure;
    configure.app_name = "D3D11 Example";
    configure.graphics_configure.width = 1280;
    configure.graphics_configure.height = 720;
    configure.graphics_configure.render_plugin_name = "d3d11_rendering_plugin";

    Context::GetInstance().Init(configure);

    Example::D3D11App myapp;
    myapp.Init();
    myapp.Run();
}
