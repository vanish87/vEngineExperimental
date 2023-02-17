#include <string>
#include <engine.hpp>
#include <vengine/rendering/data_struct.hpp>

namespace vEngine
{
    namespace Core
    {
        #define ENUM_CASE_TO_STRING(x) case x : return #x;
        #define STRING_TO_ENUM(x, str) if(#x == str) return x;

        template <typename T, typename = std::enable_if_t<std::is_integral<T>::value, T>>
        void ToString(const T& obj, std::string& to)
        {
            to = std::to_string(obj);
        }

        template <typename T, typename = std::enable_if_t<std::is_integral<T>::value, T>>
        void FromString(const std::string& obj, T& to)
        {
            to = std::stoi(obj);
        }

        void ToString(const std::string& obj, std::string& to);
        void FromString(const std::string& obj, std::string& to);

        void FromString(const std::string& obj, Rendering::ShaderType& to);

        // void ToString(const Core::UUID& uuid, std::string& str);

        // template <typename T, typename = std::enable_if_t<std::is_same<T, Core::UUID>::value, T>>
        // const Core::UUID FromString(const std::string& obj);

        // template <typename T, typename = std::enable_if_t<std::is_same<T, Rendering::ShaderType>::value, T>>
        void ToString(const Rendering::ShaderType& obj, std::string& to);

        template <typename T, typename = std::enable_if_t<std::is_same<T, Rendering::ShaderType>::value, T>>
        Rendering::ShaderType FromString(const std::string& obj);


        template <typename T, typename = std::enable_if_t<std::is_same<T, Core::GameObjectType>::value, T>>
        Core::GameObjectType FromString(const std::string& obj);

        std::string ToString(const GameObjectType& obj);

        template <typename T, typename>
        GameObjectType FromString(const std::string& str)
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
            return GameObjectType::GameObject;
        }
        // template <typename T, typename = std::enable_if_t<std::is_same<T, std::filesystem::path>::value, T>>
        // std::string ToString(const std::filesystem::path& obj)
        // {
        //     return obj.string();
        // }
    }  // namespace Core
}  // namespace vEngine