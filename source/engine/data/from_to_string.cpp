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
#define STRING_TO_ENUM(x, str, e) \
    if (#x == str)                \
    {                             \
        e = x;                    \
        return;                   \
    }
#define ENUM_TO_STRING(x, e, str) \
    if (x == e)                   \
    {                             \
        str = #x;                 \
        return;                   \
    }

        void ToString(const std::string& obj, std::string& to)
        {
            to = obj;
        }
        void FromString(const std::string& obj, std::string& to)
        {
            to = obj;
        }
        void ToString(const GameObjectType& type, std::string& str)
        {
            ENUM_TO_STRING(GameObjectType::GameObject, type, str);
            ENUM_TO_STRING(GameObjectType::GameNode, type, str);
            ENUM_TO_STRING(GameObjectType::Component, type, str);
            ENUM_TO_STRING(GameObjectType::Transform, type, str);
            ENUM_TO_STRING(GameObjectType::TransformComponent, type, str);
            ENUM_TO_STRING(GameObjectType::Camera, type, str);
            ENUM_TO_STRING(GameObjectType::CameraComponent, type, str);
            ENUM_TO_STRING(GameObjectType::Light, type, str);
            ENUM_TO_STRING(GameObjectType::LightComponent, type, str);
            ENUM_TO_STRING(GameObjectType::Mesh, type, str);
            ENUM_TO_STRING(GameObjectType::MeshComponent, type, str);
            ENUM_TO_STRING(GameObjectType::Scene, type, str);

            ENUM_TO_STRING(GameObjectType::Serializer, type, str);

            ENUM_TO_STRING(GameObjectType::Renderer, type, str);
            ENUM_TO_STRING(GameObjectType::RendererComponent, type, str);
            ENUM_TO_STRING(GameObjectType::MeshRenderer, type, str);
            ENUM_TO_STRING(GameObjectType::MeshRendererComponent, type, str);
            ENUM_TO_STRING(GameObjectType::Material, type, str);
            ENUM_TO_STRING(GameObjectType::Texture, type, str);
            ENUM_TO_STRING(GameObjectType::PipelineState, type, str);
            ENUM_TO_STRING(GameObjectType::Shader, type, str);

            ENUM_TO_STRING(GameObjectType::GraphicsBuffer, type, str);

            ENUM_TO_STRING(GameObjectType::Bone, type, str);
            ENUM_TO_STRING(GameObjectType::BoneComponent, type, str);
            ENUM_TO_STRING(GameObjectType::Joint, type, str);
            ENUM_TO_STRING(GameObjectType::AnimationClip, type, str);
            ENUM_TO_STRING(GameObjectType::Animator, type, str);
            ENUM_TO_STRING(GameObjectType::AnimatorComponent, type, str);

            ENUM_TO_STRING(GameObjectType::UI, type, str);
            ENUM_TO_STRING(GameObjectType::UIComponent, type, str);

            NOT_IMPL_ASSERT;
        }
        void FromString(const std::string& str, GameObjectType& type)
        {
            STRING_TO_ENUM(GameObjectType::GameObject, str, type);
            STRING_TO_ENUM(GameObjectType::GameNode, str, type);
            STRING_TO_ENUM(GameObjectType::Component, str, type);
            STRING_TO_ENUM(GameObjectType::Transform, str, type);
            STRING_TO_ENUM(GameObjectType::TransformComponent, str, type);
            STRING_TO_ENUM(GameObjectType::Camera, str, type);
            STRING_TO_ENUM(GameObjectType::CameraComponent, str, type);
            STRING_TO_ENUM(GameObjectType::Light, str, type);
            STRING_TO_ENUM(GameObjectType::LightComponent, str, type);
            STRING_TO_ENUM(GameObjectType::Mesh, str, type);
            STRING_TO_ENUM(GameObjectType::MeshComponent, str, type);
            STRING_TO_ENUM(GameObjectType::Scene, str, type);

            STRING_TO_ENUM(GameObjectType::Serializer, str, type);

            STRING_TO_ENUM(GameObjectType::Renderer, str, type);
            STRING_TO_ENUM(GameObjectType::RendererComponent, str, type);
            STRING_TO_ENUM(GameObjectType::MeshRenderer, str, type);
            STRING_TO_ENUM(GameObjectType::MeshRendererComponent, str, type);
            STRING_TO_ENUM(GameObjectType::Material, str, type);
            STRING_TO_ENUM(GameObjectType::Texture, str, type);
            STRING_TO_ENUM(GameObjectType::PipelineState, str, type);
            STRING_TO_ENUM(GameObjectType::Shader, str, type);

            STRING_TO_ENUM(GameObjectType::Bone, str, type);
            STRING_TO_ENUM(GameObjectType::BoneComponent, str, type);
            STRING_TO_ENUM(GameObjectType::Joint, str, type);
            STRING_TO_ENUM(GameObjectType::AnimationClip, str, type);
            STRING_TO_ENUM(GameObjectType::Animator, str, type);
            STRING_TO_ENUM(GameObjectType::AnimatorComponent, str, type);

            STRING_TO_ENUM(GameObjectType::UI, str, type);
            STRING_TO_ENUM(GameObjectType::UIComponent, str, type);

            NOT_IMPL_ASSERT;
        }
        void ToString(const Keyboard& type, std::string& str)
        {
            ENUM_TO_STRING(Keyboard::A, type, str);
            ENUM_TO_STRING(Keyboard::B, type, str);
            ENUM_TO_STRING(Keyboard::C, type, str);
            ENUM_TO_STRING(Keyboard::D, type, str);
            ENUM_TO_STRING(Keyboard::E, type, str);
            ENUM_TO_STRING(Keyboard::F, type, str);
            ENUM_TO_STRING(Keyboard::G, type, str);
            ENUM_TO_STRING(Keyboard::H, type, str);
            ENUM_TO_STRING(Keyboard::I, type, str);
            ENUM_TO_STRING(Keyboard::J, type, str);
            ENUM_TO_STRING(Keyboard::K, type, str);
            ENUM_TO_STRING(Keyboard::L, type, str);
            ENUM_TO_STRING(Keyboard::M, type, str);
            ENUM_TO_STRING(Keyboard::N, type, str);
            ENUM_TO_STRING(Keyboard::O, type, str);
            ENUM_TO_STRING(Keyboard::P, type, str);
            ENUM_TO_STRING(Keyboard::Q, type, str);
            ENUM_TO_STRING(Keyboard::R, type, str);
            ENUM_TO_STRING(Keyboard::S, type, str);
            ENUM_TO_STRING(Keyboard::T, type, str);
            ENUM_TO_STRING(Keyboard::U, type, str);
            ENUM_TO_STRING(Keyboard::V, type, str);
            ENUM_TO_STRING(Keyboard::W, type, str);
            ENUM_TO_STRING(Keyboard::X, type, str);
            ENUM_TO_STRING(Keyboard::Y, type, str);
            ENUM_TO_STRING(Keyboard::Z, type, str);

            NOT_IMPL_ASSERT;
        }
    }  // namespace Core
    namespace Rendering
    {
        void ToString(const ShaderType& type, std::string& str)
        {
            ENUM_TO_STRING(ShaderType::VertexShader, type, str);
            ENUM_TO_STRING(ShaderType::HullShader, type, str);
            ENUM_TO_STRING(ShaderType::TessellatorShader, type, str);
            ENUM_TO_STRING(ShaderType::DomainShader, type, str);
            ENUM_TO_STRING(ShaderType::GeometryShader, type, str);
            ENUM_TO_STRING(ShaderType::PixelShader, type, str);
            ENUM_TO_STRING(ShaderType::ComputeShader, type, str);
            NOT_IMPL_ASSERT;
        }
        void FromString(const std::string& str, ShaderType& type)
        {
            STRING_TO_ENUM(ShaderType::VertexShader, str, type);
            STRING_TO_ENUM(ShaderType::HullShader, str, type);
            STRING_TO_ENUM(ShaderType::TessellatorShader, str, type);
            STRING_TO_ENUM(ShaderType::DomainShader, str, type);
            STRING_TO_ENUM(ShaderType::GeometryShader, str, type);
            STRING_TO_ENUM(ShaderType::PixelShader, str, type);
            STRING_TO_ENUM(ShaderType::ComputeShader, str, type);

            NOT_IMPL_ASSERT;
        }
        void ToString(const GraphicsResourceType& type, std::string& str)
        {
            ENUM_TO_STRING(GraphicsResourceType::Index, type, str);
            ENUM_TO_STRING(GraphicsResourceType::Vertex, type, str);
            ENUM_TO_STRING(GraphicsResourceType::CBuffer, type, str);
            ENUM_TO_STRING(GraphicsResourceType::Texture, type, str);
            // ENUM_TO_STRING(GraphicsResourceType::TextureRW, type, str);
            // ENUM_TO_STRING(GraphicsResourceType::TextureW, type, str);
            ENUM_TO_STRING(GraphicsResourceType::Depth, type, str);
            NOT_IMPL_ASSERT;
        }
        void FromString(const std::string& str, GraphicsResourceType& type)
        {
            STRING_TO_ENUM(GraphicsResourceType::Index, str, type);
            STRING_TO_ENUM(GraphicsResourceType::Vertex, str, type);
            STRING_TO_ENUM(GraphicsResourceType::CBuffer, str, type);
            STRING_TO_ENUM(GraphicsResourceType::Texture, str, type);
            // STRING_TO_ENUM(GraphicsResourceType::TextureRW, str, type);
            // STRING_TO_ENUM(GraphicsResourceType::TextureW, str, type);
            STRING_TO_ENUM(GraphicsResourceType::Depth, str, type);

            NOT_IMPL_ASSERT;
        }
        void ToString(const DataFormat& format, std::string& str)
        {
            ENUM_TO_STRING(DataFormat::Undefined, format, str);
            ENUM_TO_STRING(DataFormat::RGBA32, format, str);
            ENUM_TO_STRING(DataFormat::RGFloat, format, str);
            ENUM_TO_STRING(DataFormat::RGBFloat, format, str);
            ENUM_TO_STRING(DataFormat::RGBAFloat, format, str);
            ENUM_TO_STRING(DataFormat::R32Int, format, str);
            ENUM_TO_STRING(DataFormat::RGBAInt, format, str);
            ENUM_TO_STRING(DataFormat::D24U8, format, str);
            NOT_IMPL_ASSERT;
        }
        void FromString(const std::string& str, DataFormat& format)
        {
            STRING_TO_ENUM(DataFormat::Undefined, str, format);
            STRING_TO_ENUM(DataFormat::RGBA32, str, format);
            STRING_TO_ENUM(DataFormat::RGFloat, str, format);
            STRING_TO_ENUM(DataFormat::RGBFloat, str, format);
            STRING_TO_ENUM(DataFormat::RGBAFloat, str, format);
            STRING_TO_ENUM(DataFormat::R32Int, str, format);
            STRING_TO_ENUM(DataFormat::RGBAInt, str, format);
            STRING_TO_ENUM(DataFormat::D24U8, str, format);

            NOT_IMPL_ASSERT;
        }

        void ToString(const TextureDimension& dim, std::string& str)
        {
            ENUM_TO_STRING(TextureDimension::TD_1D, dim, str);
            ENUM_TO_STRING(TextureDimension::TD_2D, dim, str);
            ENUM_TO_STRING(TextureDimension::TD_3D, dim, str);
            ENUM_TO_STRING(TextureDimension::TD_Cube, dim, str);

            NOT_IMPL_ASSERT;
        }
        void FromString(const std::string& str, TextureDimension& dim)
        {
            STRING_TO_ENUM(TextureDimension::TD_1D, str, dim);
            STRING_TO_ENUM(TextureDimension::TD_2D, str, dim);
            STRING_TO_ENUM(TextureDimension::TD_3D, str, dim);
            STRING_TO_ENUM(TextureDimension::TD_Cube, str, dim);
            NOT_IMPL_ASSERT;
        }
        void ToString(const GraphicsResourceUsage& usage, std::string& str)
        {
            ENUM_TO_STRING(GraphicsResourceUsage::CPU_GPU_ReadWrite, usage, str);
            ENUM_TO_STRING(GraphicsResourceUsage::CPU_Write_GPU_Read, usage, str);
            ENUM_TO_STRING(GraphicsResourceUsage::GPU_Read_Only, usage, str);
            ENUM_TO_STRING(GraphicsResourceUsage::GPU_ReadWrite, usage, str);

            NOT_IMPL_ASSERT;
        }
        void FromString(const std::string& str, GraphicsResourceUsage& usage)
        {
            STRING_TO_ENUM(GraphicsResourceUsage::CPU_GPU_ReadWrite, str, usage);
            STRING_TO_ENUM(GraphicsResourceUsage::CPU_Write_GPU_Read, str, usage);
            STRING_TO_ENUM(GraphicsResourceUsage::GPU_Read_Only, str, usage);
            STRING_TO_ENUM(GraphicsResourceUsage::GPU_ReadWrite, str, usage);
            NOT_IMPL_ASSERT;
        }
    }  // namespace Rendering
}  // namespace vEngine