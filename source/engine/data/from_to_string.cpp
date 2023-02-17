/// \file from_to_string.cpp
/// \brief source file for string covert
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/data/from_to_string.hpp>
#include <vengine/core/game_object.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {
        #define STRING_TO_ENUM(x, str) if(#x == str) {to = x; return;}
        #define ENUM_TO_STRING(x, str) if(x == str)  {to = #x; return;}

        void ToString(const std::string& obj, std::string& to)
        {
            to = obj;
        }
        void FromString(const std::string& obj, std::string& to)
        {
            to = obj;
        }
        void FromString(const std::string& str, Rendering::ShaderType& to)
        {
            STRING_TO_ENUM(Rendering::ShaderType::VertexShader, str);
            STRING_TO_ENUM(Rendering::ShaderType::HullShader, str);
            STRING_TO_ENUM(Rendering::ShaderType::TessellatorShader, str);
            STRING_TO_ENUM(Rendering::ShaderType::DomainShader, str);
            STRING_TO_ENUM(Rendering::ShaderType::GeometryShader, str);
            STRING_TO_ENUM(Rendering::ShaderType::PixelShader, str);
            STRING_TO_ENUM(Rendering::ShaderType::ComputeShader, str);

            NOT_IMPL_ASSERT;
        }
        void ToString(const Rendering::ShaderType& obj, std::string& to)
        {
                ENUM_TO_STRING(Rendering::ShaderType::VertexShader, obj);
                ENUM_TO_STRING(Rendering::ShaderType::HullShader, obj);
                ENUM_TO_STRING(Rendering::ShaderType::TessellatorShader, obj);
                ENUM_TO_STRING(Rendering::ShaderType::DomainShader, obj);
                ENUM_TO_STRING(Rendering::ShaderType::GeometryShader, obj);
                ENUM_TO_STRING(Rendering::ShaderType::PixelShader, obj);
                ENUM_TO_STRING(Rendering::ShaderType::ComputeShader, obj);
            NOT_IMPL_ASSERT;
        }
        void ToString(const GameObjectType& type, std::string& to)
        {
                ENUM_TO_STRING(GameObjectType::GameObject, type);
                ENUM_TO_STRING(GameObjectType::GameNode, type);
                ENUM_TO_STRING(GameObjectType::Component, type);
                ENUM_TO_STRING(GameObjectType::Transform, type);
                ENUM_TO_STRING(GameObjectType::TransformComponent, type);
                ENUM_TO_STRING(GameObjectType::Camera, type);
                ENUM_TO_STRING(GameObjectType::CameraComponent, type);
                ENUM_TO_STRING(GameObjectType::Light, type);
                ENUM_TO_STRING(GameObjectType::LightComponent, type);
                ENUM_TO_STRING(GameObjectType::Mesh, type);
                ENUM_TO_STRING(GameObjectType::MeshComponent, type);
                ENUM_TO_STRING(GameObjectType::Scene, type);

                ENUM_TO_STRING(GameObjectType::Serializer, type);

                ENUM_TO_STRING(GameObjectType::Renderer, type);
                ENUM_TO_STRING(GameObjectType::RendererComponent, type);
                ENUM_TO_STRING(GameObjectType::MeshRenderer, type);
                ENUM_TO_STRING(GameObjectType::MeshRendererComponent, type);
                ENUM_TO_STRING(GameObjectType::Material, type);
                ENUM_TO_STRING(GameObjectType::Texture, type);
                ENUM_TO_STRING(GameObjectType::PipelineState, type);
                ENUM_TO_STRING(GameObjectType::Shader, type);

                ENUM_TO_STRING(GameObjectType::Bone, type);
                ENUM_TO_STRING(GameObjectType::BoneComponent, type);
                ENUM_TO_STRING(GameObjectType::Joint, type);
                ENUM_TO_STRING(GameObjectType::AnimationClip, type);
                ENUM_TO_STRING(GameObjectType::Animator, type);
                ENUM_TO_STRING(GameObjectType::AnimatorComponent, type);
            NOT_IMPL_ASSERT;
        }
        void FromString(const std::string& str, GameObjectType& to)
        {
            STRING_TO_ENUM(GameObjectType::GameObject, str);
            STRING_TO_ENUM(GameObjectType::GameNode, str);
            STRING_TO_ENUM(GameObjectType::Component, str);
            STRING_TO_ENUM(GameObjectType::Transform, str);
            STRING_TO_ENUM(GameObjectType::TransformComponent, str);
            STRING_TO_ENUM(GameObjectType::Camera, str);
            STRING_TO_ENUM(GameObjectType::CameraComponent, str);
            STRING_TO_ENUM(GameObjectType::Light, str);
            STRING_TO_ENUM(GameObjectType::LightComponent, str);
            STRING_TO_ENUM(GameObjectType::Mesh, str);
            STRING_TO_ENUM(GameObjectType::MeshComponent, str);
            STRING_TO_ENUM(GameObjectType::Scene, str);

            STRING_TO_ENUM(GameObjectType::Serializer, str);

            STRING_TO_ENUM(GameObjectType::Renderer, str);
            STRING_TO_ENUM(GameObjectType::RendererComponent, str);
            STRING_TO_ENUM(GameObjectType::MeshRenderer, str);
            STRING_TO_ENUM(GameObjectType::MeshRendererComponent, str);
            STRING_TO_ENUM(GameObjectType::Material, str);
            STRING_TO_ENUM(GameObjectType::Texture, str);
            STRING_TO_ENUM(GameObjectType::PipelineState, str);
            STRING_TO_ENUM(GameObjectType::Shader, str);

            STRING_TO_ENUM(GameObjectType::Bone, str);
            STRING_TO_ENUM(GameObjectType::BoneComponent, str);
            STRING_TO_ENUM(GameObjectType::Joint, str);
            STRING_TO_ENUM(GameObjectType::AnimationClip, str);
            STRING_TO_ENUM(GameObjectType::Animator, str);
            STRING_TO_ENUM(GameObjectType::AnimatorComponent, str);

            NOT_IMPL_ASSERT;
        }
    }
}