
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
#include <vengine/core/material.hpp>
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

    GameObjectDescription godesc;
    godesc.type = GameObjectType::Asset;
    auto asset = GameObjectFactory::Create<Asset>(godesc);
    auto rdesc = std::make_shared<ResourceDescriptor>();
    rdesc->file_path = input;
    rdesc->complete_call_back = [&](IResourceSharedPtr c) {

    };

    asset->Load(rdesc);

    nlohmann::json j;
    ToJson(j, asset);

    std::ofstream outfile(output.string());
    outfile<<std::setw(2)<<j<<std::endl;
    // outfile<<input<<" will be compiled to "<<output<<std::endl;
    // outfile<<infile.rdbuf()<<std::endl;
    outfile.flush();
    outfile.close();
    return 0;
}
