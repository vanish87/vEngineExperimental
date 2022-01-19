#include <iostream>

// #include <windows.h>
#include <engine.hpp>
// #include <vengine/core/example_class_header.h>
#include <vengine/core/application.hpp>
#include <vengine/core/constants.hpp>
#include <vengine/core/context.hpp>
#include <version.hpp>

using namespace vEngine::Core;

class MyApp : public Application
{
    private:
        void OnCreate() override
        {
            std::cout << "User Create" << std::endl;
        }
        void OnUpdate() override
        {
            // std::cout << "User Update" << vEngine::TIME_PER_UPDATE << std::endl;
        }
};

int main(int argc, char* argv[])
{
    UNUSED_PARAMETER(argc);
    UNUSED_PARAMETER(argv);

    std::cout << "Version " + std::string(Version) << std::endl;

    Configure configure;
    configure.graphics_configure.width = 1280;
    configure.graphics_configure.height = 720;
    #ifdef VENGINE_PLATFORM_WINDOWS
    configure.graphics_configure.render_plugin_name = "d3d11_rendering_plugin";
    #else
    configure.graphics_configure.render_plugin_name = "opengl_rendering_plugin";
    #endif

    Context::GetInstance().ConfigureWith(configure);

    MyApp myapp;
    myapp.Init();
    myapp.Run();
}
