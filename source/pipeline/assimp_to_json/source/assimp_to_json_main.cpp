
#include <engine.hpp>
#include <fstream>
#include <filesystem>

#include <vengine/data/meta.hpp>
#include <vengine/data/json.hpp>
#include <vengine/core/scene.hpp>

#include <assimp_handler.hpp>

int main(int argc, char* argv[])
{
    std::filesystem::path input;
    std::filesystem::path output;
    std::filesystem::path resource;
    for(auto i = 0; i < argc; ++i)
    {
        auto s = std::string(argv[i]);
        if(s == "-i") input = argv[i+1];
        if(s == "-o") output = argv[i+1];
        if(s == "-r") resource = argv[i+1];
    }

    Configure configure;
    configure.graphics_configure.width = 320;
    configure.graphics_configure.height = 240;
    configure.resource_root = resource;

    #ifdef VENGINE_PLATFORM_WINDOWS
    configure.graphics_configure.render_plugin_name = "d3d11_rendering_plugin";
    #else
    configure.graphics_configure.render_plugin_name = "opengl_rendering_plugin";
    #endif
    Context::GetInstance().Init(configure);

    // input = "C:/Users/liyuan/Documents/Personal/vEngineExperimental/resource/boblamp/boblampclean.md5mesh";
    // output = "C:/Users/liyuan/Documents/Personal/vEngineExperimental/build_windows/resource/bin/assimp/boblampclean.json";

    PRINT(resource.string());


    vEngine::Pipeline::AssimpHandler handler;
    handler.Init();
    auto scene = handler.LoadFromAssimp(input);

    nlohmann::json j;
    ToJson(j, scene);
    PRINT("Save to "<<output.string());
    // FromJson(j, scene);
    std::ofstream outfile(output.string());
    outfile<<std::setw(2)<<j<<std::endl;
    // outfile<<input<<" will be compiled to "<<output<<std::endl;
    // outfile<<infile.rdbuf()<<std::endl;
    outfile.flush();
    outfile.close();

    
    return 0;
    // std::ifstream infile(input);
    // auto base_path = input.parent_path().parent_path().string();
    // ResourceLoader::GetInstance().AddSearchPath(base_path);
    // // ResourceLoader::GetInstance().AddSearchPath("resource");
    // ResourceLoader::GetInstance().AddSearchPath(base_path + "/shader");

    // auto scene = GameObjectFactory::Create<Scene>();
    // auto rdesc = std::make_shared<ResourceDescriptor>();
    // rdesc->file_path = input;
    // rdesc->complete_call_back = [&](IResourceSharedPtr c) {

    // };

    // scene->Load(rdesc);
}
