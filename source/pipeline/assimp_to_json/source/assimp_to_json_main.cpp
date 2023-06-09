
#include <engine.hpp>
#include <fstream>
#include <filesystem>

#include <engine.hpp>
#include <vengine/core/resource_manager.hpp>
#include <vengine/core/scene.hpp>
#include <vengine/core/game_object_factory.hpp>
#include <vengine/animation/bone_component.hpp>

#include <assimp_handler.hpp>

using namespace vEngine::Core;

int main(int argc, char* argv[])
{
    std::filesystem::path input;
    std::filesystem::path output;
    std::filesystem::path resource_src;
    std::filesystem::path resource_bin;
    for (auto i = 0; i < argc; ++i)
    {
        auto s = std::string(argv[i]);
        if (s == "-i") input = argv[i + 1];
        if (s == "-o") output = argv[i + 1];
        if (s == "-r") resource_src = argv[i + 1];
        if (s == "-b") resource_bin = argv[i + 1];
    }
    // std::string prefix = "C:/Users/vanis/Documents/Code/vEngineExperimental";
    // std::string prefix = "C:/Users/liyuan/Documents/Personal/vEngineExperimental";
    // input = prefix + "/resource/boblamp/boblampclean.md5mesh";
    // output = prefix + "/build_windows/resource/bin/assimp/boblampclean.json";
    // resource_src = prefix + "/resource";
    // resource_bin = prefix + "/build_windows/resource/bin";

    Configure configure;
    configure.app_name = "assimp_to_json";
    configure.graphics_configure.output = Output::CommandLine;
    configure.resource_src = resource_src;
    configure.resource_bin = resource_bin;


#ifdef VENGINE_PLATFORM_WINDOWS
    configure.graphics_configure.render_plugin_name = "d3d11_rendering_plugin";
#else
    configure.graphics_configure.render_plugin_name = "opengl_rendering_plugin";
#endif
    Context::GetInstance().SetConfigure(configure);

    Context::GetInstance().Init();
    ResourceManager::GetInstance().Init();
    // ResourceManager::GetInstance().SetRoot(configure.resource_src);
    // ResourceLoader::GetInstance().AddSearchFolder("resource");
    // ResourceManager::GetInstance().AddSearchFolder("shader");
    // ResourceManager::GetInstance().AddSearchFolder("sponza");
    // ResourceManager::GetInstance().AddSearchFolder("bob");
    // ResourceManager::GetInstance().AddSearchFolder("boblamp");

    // PRINT(resource_src.string());
    // PRINT(resource_bin.string());

    vEngine::Pipeline::AssimpHandler handler;

    auto scene = handler.LoadFromAssimp(input);
    ResourceManager::GetInstance().Save(scene, output);
    ResourceManager::GetInstance().SaveContext();
    PRINT("Save to " << output.string());
    // auto j = ToJson(scene);
    // SaveJson(j, output);

    scene.reset();

    // auto path = ResourceLoader::GetInstance().GetFilePath("boblampclean.json");
    // Context::GetInstance().Clear();
    // auto path = output;
    // auto new_scene = ResourceManager::GetInstance().Load(output);
    // new_scene.reset();

    ResourceManager::GetInstance().Deinit();
    Context::GetInstance().Deinit();

    return 0;
}
