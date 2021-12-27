#include <iostream>

// #include <windows.h>
#include <engine.hpp>
// #include <vengine/core/example_class_header.h>
#include <version.hpp>

#include <vengine/core/application.hpp>



using namespace vEngine::Core;

class MyApp : public Application
{

    private:

    void OnCreate() override
    {

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

    MyApp myapp;
    myapp.Init();
    myapp.Run();
}
