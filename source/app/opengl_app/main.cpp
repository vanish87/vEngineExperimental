#include <engine.hpp>
#include <version.hpp>
#include <vengine/core/application.hpp>
#include <vengine/core/context.hpp>

using namespace vEngine::Core;

namespace Example
{
    class OpenGLApp : public Application
    {
    };
}  // namespace Example

int main(int argc, char* argv[])
{
    UNUSED_PARAMETER(argc);
    UNUSED_PARAMETER(argv);

    std::cout << "Version " + std::string(Version) << std::endl;

    Configure configure;
    configure.app_name = "OpenGL Example";
    configure.graphics_configure.width = 1280;
    configure.graphics_configure.height = 720;
    configure.graphics_configure.render_plugin_name = "opengl_rendering_plugin";

    Context::GetInstance().ConfigureWith(configure);

    Example::OpenGLApp myapp;
    myapp.Init();
    myapp.Run();
}
