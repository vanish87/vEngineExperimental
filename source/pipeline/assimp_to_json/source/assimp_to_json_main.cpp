
#include <engine.hpp>
#include <fstream>
#include <filesystem>

#include <vengine/data/meta.hpp>
#include <vengine/data/json.hpp>
#include <vengine/core/scene.hpp>

#include <assimp_handler.hpp>

#include <class_foo.hpp>
#include <vengine/data/json_test.hpp>

int main(int argc, char* argv[])
{
    std::filesystem::path input;
    std::filesystem::path output;
    std::filesystem::path resource_src;
    std::filesystem::path resource_bin;
    for(auto i = 0; i < argc; ++i)
    {
        auto s = std::string(argv[i]);
        if(s == "-i") input = argv[i+1];
        if(s == "-o") output = argv[i+1];
        if(s == "-r") resource_src = argv[i+1];
        if(s == "-b") resource_bin = argv[i+1];
    }
    input = "C:/Users/liyuan/Documents/Personal/vEngineExperimental/resource/boblamp/boblampclean.md5mesh";
    output = "C:/Users/liyuan/Documents/Personal/vEngineExperimental/build_windows/resource/bin/assimp/boblampclean.json";
    resource_src = "C:/Users/liyuan/Documents/Personal/vEngineExperimental/resource";
    resource_bin = "C:/Users/liyuan/Documents/Personal/vEngineExperimental/build_windows/resource/bin";

    Configure configure;
    configure.graphics_configure.width = 320;
    configure.graphics_configure.height = 240;
    configure.resource_src = resource_src;
    configure.resource_bin = resource_bin;

    #ifdef VENGINE_PLATFORM_WINDOWS
    configure.graphics_configure.render_plugin_name = "d3d11_rendering_plugin";
    #else
    configure.graphics_configure.render_plugin_name = "opengl_rendering_plugin";
    #endif
    Context::GetInstance().Init(configure);
    ResourceLoader::GetInstance().AddSearchPath(configure.resource_src);
    // ResourceLoader::GetInstance().AddSearchFolder("resource");
    ResourceLoader::GetInstance().AddSearchFolder("shader");
    ResourceLoader::GetInstance().AddSearchFolder("sponza");
    ResourceLoader::GetInstance().AddSearchFolder("bob");
    ResourceLoader::GetInstance().AddSearchFolder("boblamp");

    PRINT(resource_src.string());
    PRINT(resource_bin.string());


    vEngine::Pipeline::AssimpHandler handler;
    handler.Init();
    auto scene = handler.LoadFromAssimp(input);

    auto base_class = GameObjectFactory::Create<ClassFoo>();
    auto j = ToJson(base_class);
    // auto j = ToJsonTest(base_class);
    // auto j = ToJsonTest(base_class);

    std::shared_ptr<ClassFoo> foo_ptr;
    base_class = foo_ptr;

    GameObjectSharedPtr new_base_class;
    FromJson(j, new_base_class);


    PRINT("Save to "<<output.string());
    j = ToJson(scene);
    std::ofstream outfile(output.string());
    outfile<<std::setw(2)<<j<<std::endl;
    // outfile<<input<<" will be compiled to "<<output<<std::endl;
    // outfile<<infile.rdbuf()<<std::endl;
    outfile.flush();
    outfile.close();

    handler.Deinit();
    Context::GetInstance().Deinit();

    return 0;
    // std::ifstream infile(input);
    // auto base_path = input.parent_path().parent_path().string();
    // ResourceLoader::GetInstance().AddSearchPath(base_path);
    // // ResourceLoader::GetInstance().AddSearchPath("resource");
    // ResourceLoader::GetInstance().AddSearchPath(base_path + "/shader");

    // auto scene = GameObjectFactory::Create<Scene>();
    // auto rdesc = std::make_shared<ResourceDescriptor>();
    // rdesc->file_path = input;
    // rdesc->on_complete_call_back = [&](IResourceSharedPtr c) {

    // };

    // scene->Load(rdesc);
}
