
#include <engine.hpp>
#include <fstream>
#include <filesystem>

#include <vengine/core/game_node.hpp>
#include <vengine/core/iresource.hpp>
#include <vengine/core/vector.hpp>
#include <vengine/core/game_node_factory.hpp>
#include <vengine/core/game_object_factory.hpp>
#include <vengine/animation/bone.hpp>
#include <vengine/animation/bone_component.hpp>
#include <vengine/animation/joint.hpp>
#include <vengine/animation/joint_component.hpp>
#include <vengine/animation/skeleton.hpp>
#include <vengine/animation/skeleton_component.hpp>
#include <vengine/animation/animation_clip.hpp>
#include <vengine/animation/animator_component.hpp>
#include <vengine/core/camera_component.hpp>
#include <vengine/rendering/material.hpp>
#include <vengine/core/mesh.hpp>
#include <vengine/core/mesh_renderer_component.hpp>
#include <vengine/core/resource_loader.hpp>
#include <vengine/core/iresource.hpp>
#include <vengine/core/transform_component.hpp>
#include <vengine/core/asset_component.hpp>

#include <vengine/data/meta.hpp>
#include <vengine/data/json.hpp>
int main(int argc, char* argv[])
{
    Configure configure;
    configure.graphics_configure.width = 1280;
    configure.graphics_configure.height = 720;
    #ifdef VENGINE_PLATFORM_WINDOWS
    configure.graphics_configure.render_plugin_name = "d3d11_rendering_plugin";
    #else
    configure.graphics_configure.render_plugin_name = "opengl_rendering_plugin";
    #endif
    Context::GetInstance().ConfigureWith(configure);
    Context::GetInstance().GetRenderEngine().Init();

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
    auto base_path = input.parent_path().parent_path().string();
    ResourceLoader::GetInstance().AddSearchPath(base_path);
    // ResourceLoader::GetInstance().AddSearchPath("resource");
    ResourceLoader::GetInstance().AddSearchPath(base_path + "/shader");

    auto scene = GameObjectFactory::Create<Scene>();
    auto rdesc = std::make_shared<ResourceDescriptor>();
    rdesc->file_path = input;
    rdesc->complete_call_back = [&](IResourceSharedPtr c) {

    };

    scene->Load(rdesc);

    nlohmann::json j;
    ToJson(j, scene);

    PRINT("Save to"<<output.string());

    FromJson(j, scene);

    std::ofstream outfile(output.string());
    outfile<<std::setw(2)<<j<<std::endl;
    // outfile<<input<<" will be compiled to "<<output<<std::endl;
    // outfile<<infile.rdbuf()<<std::endl;
    outfile.flush();
    outfile.close();
    return 0;
}
