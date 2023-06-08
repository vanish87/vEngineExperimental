
#include <fstream>
#include <filesystem>

#include <engine.hpp>
#include <vengine/core/game_object_factory.hpp>
#include <vengine/core/resource_manager.hpp>
#include <vengine/rendering/shader.hpp>

using namespace vEngine::Core;
using namespace vEngine::Rendering;

ShaderType ProfileToShaderType(const std::string& profile)
{
    if(profile == "vs") return ShaderType::VertexShader;
    if(profile == "hs") return ShaderType::HullShader;
    if(profile == "ts") return ShaderType::TessellatorShader;
    if(profile == "ds") return ShaderType::DomainShader;
    if(profile == "gs") return ShaderType::GeometryShader;
    if(profile == "ps") return ShaderType::PixelShader;
    if(profile == "cs") return ShaderType::ComputeShader;

    return ShaderType::VertexShader;
}

int main(int argc, char* argv[])
{
    std::filesystem::path input;
    std::filesystem::path output;
    std::filesystem::path resource_src;
    std::filesystem::path resource_bin;
    std::string profile;
    for (auto i = 0; i < argc; ++i)
    {
        auto s = std::string(argv[i]);
        if (s == "-i") input = argv[i + 1];
        if (s == "-o") output = argv[i + 1];
        if (s == "-r") resource_src = argv[i + 1];
        if (s == "-b") resource_bin = argv[i + 1];
        if (s == "-p") profile = argv[i + 1];
    }
    // input = "C:/Users/liyuan/Documents/Personal/vEngineExperimental/resource/shader/ps/ps.hlsl";
    // output = "C:/Users/liyuan/Documents/Personal/vEngineExperimental/build_windows/resource/bin/shader/ps/ps.json";
    // resource_src = "C:/Users/liyuan/Documents/Personal/vEngineExperimental/resource";
    // resource_bin = "C:/Users/liyuan/Documents/Personal/vEngineExperimental/build_windows/resource/bin";

    Configure configure;
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

    auto shader = std::dynamic_pointer_cast<Shader>(ResourceManager::GetInstance().Load(output));
    if (shader == nullptr) shader = GameObjectFactory::Create<GameObjectType::Shader, Shader>();

    shader->type = ProfileToShaderType(profile);

    std::ifstream fin(input);

    if (!fin)
    {
        PRINT_AND_BREAK("Cannot open hlsl File ");
        return -1;
    }

    fin.seekg(0, std::ios_base::end);
    auto size = fin.tellg();
    fin.seekg(0, std::ios_base::beg);
    shader->content.resize(size);

    fin.read(shader->content.data(), size);
    fin.close();

    ResourceManager::GetInstance().Save(shader, output);
    ResourceManager::GetInstance().SaveContext();

    ResourceManager::GetInstance().Deinit();
    Context::GetInstance().Deinit();
    return 0;
}
