
#include <engine.hpp>
#include <fstream>
#include <filesystem>

int main(int argc, char* argv[])
{
    UNUSED_PARAMETER(argc);
    UNUSED_PARAMETER(argv);
    std::filesystem::path input;
    std::filesystem::path output;
    for(auto i = 0; i < argc; ++i)
    {
        auto s = std::string(argv[i]);
        if(s == "-i") input = argv[i+1];
        if(s == "-o") output = argv[i+1];
    }
    std::ifstream infile(input);
    std::ofstream outfile(output.string());
    outfile<<input<<" will be compiled to "<<output<<std::endl;
    outfile<<infile.rdbuf()<<std::endl;
    outfile.flush();
    outfile.close();
    return 0;
}
