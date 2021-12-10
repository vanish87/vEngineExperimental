#include <iostream>

#include <engine.hpp>
#include <version.hpp>

using namespace vEngine::Core;
int main(int argc, char* argv[])
{
    std::cout << "Version " + std::string(Version) << std::endl;
}