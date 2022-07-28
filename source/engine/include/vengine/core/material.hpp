/// \file material.hpp
/// \brief Head file for Material
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_MATERIAL_HPP
#define _VENGINE_CORE_MATERIAL_HPP

#include <filesystem>

#include <engine.hpp>
#include <vengine/core/game_object.hpp>
#include <vengine/core/iresource.hpp>
#include <vengine/rendering/data_struct.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        struct MaterialResourceDesc : public ResourceDescriptor
        {
                std::unordered_map<Rendering::ShaderType, std::filesystem::path> shaders;
        };

        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class Material : public GameObject, public IResource
        {
            public:
                constexpr static auto properties()
                {
                    return std::tuple_cat(
                        GameObject::properties(),
                        std::make_tuple(
                            property("pipeline_state", &Material::pipeline_state_)
                        )
                    );
                };
            public:
                static MaterialSharedPtr Default();

                /// \brief brief constructor description.
                Material();
                ~Material();
                // void SetShader(const std::filesystem::path path, const ShaderType type);

                bool Load(const ResourceDescriptorSharedPtr descriptor) override;
                ResourceState CurrentState() override;

                void UpdateGPUResource();


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
                ResourceState current_state_ = ResourceState::Unknown;

                Rendering::PipelineStateSharedPtr pipeline_state_;

                // maybe layout like D3D11_INPUT_ELEMENT_DESC

                Rendering::GraphicsBufferSharedPtr constant_buffer_;
                std::vector<Rendering::TextureSharedPtr> textures_;

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
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_MATERIAL_HPP */
