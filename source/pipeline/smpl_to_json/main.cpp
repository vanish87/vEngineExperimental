
#include <engine.hpp>
#include <fstream>

int main(int argc, char* argv[])
{
    UNUSED_PARAMETER(argc);
    UNUSED_PARAMETER(argv);
    std::ofstream outfile("my.json");
    outfile<<"MyJson"<<std::endl;
    outfile.flush();
    outfile.close();
    return 0;
}
