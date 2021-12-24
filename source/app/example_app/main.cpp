#include <iostream>

#include <engine.hpp>
#include <version.hpp>

using namespace vEngine::Core;

class MyApp : public Application
{

};

int main(int argc, char* argv[])
{
    UNUSED_PARAMETER(argc);
    UNUSED_PARAMETER(argv);
    
    std::cout << "Version " + std::string(Version) << std::endl;
    #ifdef WINDOWS
    std::cout << "Windows"<<std::endl;
    #endif

    MyApp myapp;
    myapp.Run();
}
