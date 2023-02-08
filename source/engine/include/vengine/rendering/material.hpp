/// \file material.hpp
/// \brief Head file for Material
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_RENDERING_MATERIAL_HPP
#define _VENGINE_RENDERING_MATERIAL_HPP


#include <engine.hpp>
#include <vengine/core/game_object.hpp>
#include <vengine/rendering/data_struct.hpp>
#include <vengine/rendering/shader.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Rendering
    {
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class VENGINE_API Material : public Core::GameObject
        {
            public:
                constexpr static auto properties()
                {
                    return std::tuple_cat(
                        GameObject::properties(), 
                        std::make_tuple(
                            property("pipeline_state", &Material::pipeline_state_), 
                            property("textures", &Material::textures_)
                            ));
                };

            public:
                static MaterialSharedPtr Default();

                /// \brief brief constructor description.
                Material(const Core::GameObjectType type = Core::GameObjectType::Material);
                ~Material();
                // void SetShader(const std::filesystem::path path, const ShaderType type);

                void UpdateGPUResource();
                void BindShader(const ShaderType type, const ShaderSharedPtr shader);
                void BindTexture(const std::string name, const TextureSharedPtr texture);

                // color
                // parameter
                // normal map
                // etc.

                // shader and shader input layout
                //  D3D11_INPUT_ELEMENT_DESC input_desc[] = { {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
                //  {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
                //  };

                // all vs/ps related data is stored in PipelineState
                // std::string vs_name_;
                // std::string ps_name_;

                Rendering::PipelineStateSharedPtr pipeline_state_;

                // maybe layout like D3D11_INPUT_ELEMENT_DESC

                Rendering::GraphicsBufferSharedPtr constant_buffer_;
                std::unordered_map<std::string, Rendering::TextureSharedPtr> textures_;

                // parameter example
                // template <typename T>
                // struct ParameterMap
                // {
                //         bool bUsingSingleValue = true;

                //         union _ParameterMap
                //         {
                //                 T Value;
                //                 std::shared_ptr<image> Map;
                //         };
                // };

                // typedef ParameterMap<float4> Color;
                // typedef ParameterMap<float3> Normal;
                // typedef ParameterMap<float> Parameter;
        };
    }  // namespace Rendering
}  // namespace vEngine

#endif /* _VENGINE_RENDERING_MATERIAL_HPP */
