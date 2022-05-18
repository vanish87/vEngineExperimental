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

#include <engine.hpp>
#include <vengine/core/game_object.hpp>
#include <vengine/core/iresource.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        using namespace Rendering;
        
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class Material : public GameObject, IResource
        {
            public:
                /// \brief brief constructor description.
                Material(const std::string vs_name, const std::string ps_name);
                ~Material()
                {
                    // PRINT("Destory material");
                }

                bool Load() override;

                // color
                // parameter
                // normal map
                // etc.

                // shader and shader input layout
                //  D3D11_INPUT_ELEMENT_DESC input_desc[] = { {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
                //  {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
                //  };

                //all vs/ps related data is stored in PipelineState
                std::string vs_name_;
                std::string ps_name_;
                PipelineStateSharedPtr pipeline_state_;

                // maybe layout like D3D11_INPUT_ELEMENT_DESC

                GraphicsBufferSharedPtr constant_buffer_;
                std::vector<Rendering::TextureSharedPtr> textures_;

                //paramter example
                // template <typename T>
                // struct ParameterMap
                // {
                //         bool bUsingSingleValue = true;

                //         union _ParameterMap
                //         {
                //                 T Value;
                //                 std::shared_ptr<Image> Map;
                //         };
                // };

                // typedef ParameterMap<Vector4f> Color;
                // typedef ParameterMap<Vector3f> Normal;
                // typedef ParameterMap<float> Parameter;
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_MATERIAL_HPP */
