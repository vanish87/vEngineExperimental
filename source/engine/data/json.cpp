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
        json ToJson(const std::vector<char>& vector)
        {
            return json(std::string(vector.begin(), vector.end()));
        }
        json ToJson(const std::filesystem::path& path)
        {
            return json(path.string());
        }
        json ToJson(const UUID& uuid)
        {
            return json(uuid.AsUint());
        }
        json ToJson(const Rendering::ShaderType& shader_type)
        {
            return json(ToString<Rendering::ShaderType>(shader_type));
        }
        json ToJson(const GameObjectType& go_type)
        {
            return json(ToString<GameObjectType>(go_type));
        }
        void FromJson(const json& j, UUID& uuid)
        {
            auto id = j.get<uint64_t>();
            uuid.Set(id);
        }
        void FromJson(const json& j, std::filesystem::path& path)
        {
            auto data = j.get<std::string>();
            path = data;
        }
        void FromJson(const json& j, GameObjectType& go_type)
        {
            auto data = j.get<std::string>();
            go_type = FromString<GameObjectType>(data);
            // NOT_IMPL_ASSERT;
            // UNUSED_PARAMETER(j);
            // UNUSED_PARAMETER(go_type);
            // return json(ToString<GameObjectType>(go_type));
        }
        void FromJson(const json& j, Rendering::ShaderType& shader_type)
        {
            auto data = j.get<std::string>();
            shader_type = FromString<Rendering::ShaderType>(data);
            // NOT_IMPL_ASSERT;
            // UNUSED_PARAMETER(j);
            // UNUSED_PARAMETER(shader_type);
            // return json(ToString<GameObjectType>(go_type));
        }
        void FromJson(const json& j, std::vector<char>& vector)
        {
            vector.clear();
            auto data = j.get<std::string>();
            for (const auto& it : data)
            {
                vector.push_back(it);
            }
        }
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
    }  // namespace Core

}  // namespace vEngine