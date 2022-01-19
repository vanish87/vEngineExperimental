#include <iostream>

// #include <windows.h>
#include <engine.hpp>
// #include <vengine/core/example_class_header.h>
#include <version.hpp>

#include <vengine/core/application.hpp>
#include <vengine/core/context.hpp>



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

    }

};

int main(int argc, char* argv[])
{
    UNUSED_PARAMETER(argc);
    UNUSED_PARAMETER(argv);

    std::cout << "Version " + std::string(Version) << std::endl;
    #ifdef WINDOWS
    std::cout << "Windows"<<std::endl;
    #endif

    // MyNamespace::MyClass cla;
    // Context::GetIntstance().Setup();

    Configure configure;
    // configure.graphics_configure.width = 1920;
    // configure.graphics_configure.height = 1080;
    #ifdef VENGINE_PLATFORM_WINDOWS
        configure.graphics_configure.render_plugin_name = "d3d11_rendering_plugin";
    #endif
    Context::GetInstance().ConfigureWith(configure);

    MyApp myapp;
    myapp.Init();
    myapp.Run();
}
