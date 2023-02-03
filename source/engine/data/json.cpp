/// \file json.inc
/// \brief source file for json
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/data/json.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {
        template <>
        json ToJson(const std::filesystem::path& path)
        {
            return json(path.string());
        }
        template <>
        json ToJson(const UUID& uuid)
        {
            return json(uuid.AsUint());
        }
        template <>
        json ToJson(const Rendering::ShaderType& shader_type)
        {
            return json(ToString<Rendering::ShaderType>(shader_type));
        }
        template <>
        json ToJson(const GameObjectType& go_type)
        {
            return json(ToString<GameObjectType>(go_type));
        }
        // template <>
        // json ToJson(const std::vector<char>& vector)
        // {
        //     return json(std::string(vector.begin(), vector.end()));
        // }
        template <>
        void FromJson(const json& j, UUID& uuid)
        {
            auto id = j.get<uint64_t>();
            uuid.Set(id);
        }
        template <>
        void FromJson(const json& j, std::filesystem::path& path)
        {
            auto data = j.get<std::string>();
            path = data;
        }
        template <>
        void FromJson(const json& j, GameObjectType& go_type)
        {
            auto data = j.get<std::string>();
            go_type = FromString<GameObjectType>(data);
            // NOT_IMPL_ASSERT;
            // UNUSED_PARAMETER(j);
            // UNUSED_PARAMETER(go_type);
            // return json(ToString<GameObjectType>(go_type));
        }
        template <>
        void FromJson(const json& j, Rendering::ShaderType& shader_type)
        {
            auto data = j.get<std::string>();
            shader_type = FromString<Rendering::ShaderType>(data);
            // NOT_IMPL_ASSERT;
            // UNUSED_PARAMETER(j);
            // UNUSED_PARAMETER(shader_type);
            // return json(ToString<GameObjectType>(go_type));
        }
        // template <>
        // void FromJson(const json& j, std::vector<char>& vector)
        // {
        //     vector.clear();
        //     auto data = j.get<std::string>();
        //     for (const auto& it : data)
        //     {
        //         vector.push_back(it);
        //     }
        // }
        std::string ToString(const GameObjectType& obj)
        {
            switch (obj)
            {
                ENUM_CASE_TO_STRING(GameObjectType::GameObject);
                ENUM_CASE_TO_STRING(GameObjectType::GameNode);
                ENUM_CASE_TO_STRING(GameObjectType::Component);
                ENUM_CASE_TO_STRING(GameObjectType::Transform);
                ENUM_CASE_TO_STRING(GameObjectType::TransformComponent);
                ENUM_CASE_TO_STRING(GameObjectType::Camera);
                ENUM_CASE_TO_STRING(GameObjectType::CameraComponent);
                ENUM_CASE_TO_STRING(GameObjectType::Light);
                ENUM_CASE_TO_STRING(GameObjectType::LightComponent);
                ENUM_CASE_TO_STRING(GameObjectType::Mesh);
                ENUM_CASE_TO_STRING(GameObjectType::MeshComponent);
                ENUM_CASE_TO_STRING(GameObjectType::Scene);

                ENUM_CASE_TO_STRING(GameObjectType::Serializer);

                ENUM_CASE_TO_STRING(GameObjectType::Renderer);
                ENUM_CASE_TO_STRING(GameObjectType::RendererComponent);
                ENUM_CASE_TO_STRING(GameObjectType::MeshRenderer);
                ENUM_CASE_TO_STRING(GameObjectType::MeshRendererComponent);
                ENUM_CASE_TO_STRING(GameObjectType::Material);
                ENUM_CASE_TO_STRING(GameObjectType::Texture);
                ENUM_CASE_TO_STRING(GameObjectType::PipelineState);
                ENUM_CASE_TO_STRING(GameObjectType::Shader);

                ENUM_CASE_TO_STRING(GameObjectType::Bone);
                ENUM_CASE_TO_STRING(GameObjectType::BoneComponent);
                ENUM_CASE_TO_STRING(GameObjectType::Joint);
                ENUM_CASE_TO_STRING(GameObjectType::AnimationClip);
                ENUM_CASE_TO_STRING(GameObjectType::Animator);
                ENUM_CASE_TO_STRING(GameObjectType::AnimatorComponent);
                default:
                    break;
            }
            NOT_IMPL_ASSERT;
            return "NOT DEFINED";
        }
        void SaveJson(const json& j, const std::filesystem::path& path)
        {
            auto folder = path.parent_path();
            if(!std::filesystem::exists(folder)) std::filesystem::create_directories(folder);

            std::ofstream outfile(path.string());
            outfile << std::setw(2) << j << std::endl;
            outfile.flush();
            outfile.close();
        }
        std::filesystem::path GameObjectToPath(const GameObjectDescriptor& desc)
        {
            auto config = Context::GetInstance().CurrentConfigure();
            auto path = config.resource_bin;
            auto context_name = config.context_name;
            // auto gn = std::dynamic_pointer_cast<GameNode>(go);
            // if(gn != nullptr)
            // {
            //     while(gn != nullptr)
            //     {
            //         path /= gn->descriptor_.name;
            //     }
            // }

            auto name = desc.name;
            auto type = ToString(desc.type);

            auto file_name = std::to_string(desc.uuid.AsUint()) + "_" + name + "_" + type + ".json";

            std::string illegal = ":\"\'<>%$*&+ ";
            for (auto c : illegal)
            {
                std::replace(file_name.begin(), file_name.end(), c, '_');
            }

            return path / context_name / file_name;
        }
        json LoadJson(const std::filesystem::path path)
        {
            std::ifstream file(path.string());
            auto j = json::parse(file);
            file.close();
            return j;
        }
    }  // namespace Core

}  // namespace vEngine