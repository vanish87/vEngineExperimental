
#include <engine.hpp>
#include <fstream>
#include <filesystem>

#include <vengine/data/meta.hpp>
#include <vengine/data/json.hpp>
#include <vengine/core/scene.hpp>
#include <vengine/core/light.hpp>

#include <assimp_handler.hpp>

#include <vengine/data/json_test.hpp>
#include <vengine/data/class_foo.hpp>

void TestFunction(std::filesystem::path output)
{
    GameObjectSharedPtr foo_class = GameObjectFactory::Create<ClassFoo>();
    auto foo = std::dynamic_pointer_cast<ClassFoo>(foo_class);
    foo->pos = float4(1, 2, 3, 4);
    foo->content = "this is new content";
    foo->matrix = float4x4::Identity();

    auto j = ToJson(foo_class);

    std::ofstream outfile(output.string());
    outfile << std::setw(2) << j << std::endl;
    outfile.flush();
    outfile.close();

    Context::GetInstance().Clear();
    GameObjectSharedPtr foo_ptr;
    j = LoadJson(output);
    FromJson(j, foo_ptr);

    auto fptr = std::dynamic_pointer_cast<ClassFoo>(foo_ptr);
    PRINT(fptr->content);
    PRINT(fptr->matrix[1][1]);
    PRINT(fptr->pos.x() << " " << fptr->pos.y() << " " << fptr->pos.z() << " " << fptr->pos.w());

    // auto go = GameObjectFactory::Create<ClassFoo>();
    // auto foo_p = std::dynamic_pointer_cast<ClassFoo>(go);

    // PRINT(foo_p->content);
}

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
    input = "C:/Users/liyuan/Documents/Personal/vEngineExperimental/resource/boblamp/boblampclean.md5mesh";
    output = "C:/Users/liyuan/Documents/Personal/vEngineExperimental/build_windows/resource/bin/assimp/boblampclean.json";
    resource_src = "C:/Users/liyuan/Documents/Personal/vEngineExperimental/resource";
    resource_bin = "C:/Users/liyuan/Documents/Personal/vEngineExperimental/build_windows/resource/bin";

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
    ResourceLoader::GetInstance().AddSearchPath(configure.resource_src);
    // ResourceLoader::GetInstance().AddSearchFolder("resource");
    ResourceLoader::GetInstance().AddSearchFolder("shader");
    ResourceLoader::GetInstance().AddSearchFolder("sponza");
    ResourceLoader::GetInstance().AddSearchFolder("bob");
    ResourceLoader::GetInstance().AddSearchFolder("boblamp");

    PRINT(resource_src.string());
    PRINT(resource_bin.string());

    vEngine::Pipeline::AssimpHandler handler;
    
    auto go = GameObjectFactory::Create<GameObjectType::Mesh>();

    auto mesh = GameObjectFactory::Create<GameObjectType::Mesh, vEngine::Core::Mesh>();
    // auto mesh = Context::GetInstance().Create<GameObjectType::Mesh, vEngine::Core::Mesh>();
    PRINT(mesh->description_.name);

    // auto camera = GameObjectFactory::Create<GameObjectType::Camera, vEngine::Core::Camera>(mesh->description_);
    // PRINT(camera->description_.name);

    // auto light = GameObjectFactory::Create<GameObjectType::Light, vEngine::Core::Light>(1234);
    // PRINT(light->description_.name);

    auto scene = handler.LoadFromAssimp(input);
    PRINT("Save to " << output.string());
    auto j = ToJson(scene);
    std::ofstream outfile(output.string());
    outfile << std::setw(2) << j << std::endl;
    outfile.flush();
    outfile.close();

    scene.reset();

    // auto path = ResourceLoader::GetInstance().GetFilePath("boblampclean.json");
    Context::GetInstance().Clear();
    auto path = output;
    auto new_scene = Scene::Load(path);

    Context::GetInstance().Deinit();

    return 0;
}
