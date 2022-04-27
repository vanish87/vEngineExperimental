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

#include <vengine/core/game_object.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class Material : public GameObject
        {
            public:
                /// \brief brief constructor description.
                Material();

                void Load();

                //color
                //parameter
                //normal map
                //etc.

                //shader and shader input layout
                // D3D11_INPUT_ELEMENT_DESC input_desc[] = { {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
                // {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
                // };

                std::string vs_name_;
                std::string ps_name_;

                //maybe layout like D3D11_INPUT_ELEMENT_DESC

                Rendering::GraphicsBufferSharedPtr constant_buffer_;
                std::vector<Rendering::TextureSharedPtr> textures_;




        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_MATERIAL_HPP */
