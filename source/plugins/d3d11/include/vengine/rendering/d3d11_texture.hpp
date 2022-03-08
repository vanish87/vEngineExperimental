/// \file d3d11_texture.hpp
/// \brief Head file for D3D11Texture
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_RENDERING_D3D11_TEXTURE_HPP
#define _VENGINE_RENDERING_D3D11_TEXTURE_HPP

#include <vengine/rendering/texture.hpp>

namespace vEngine
{
    namespace Rendering
    {
        /// \brief Unity-like Graphics buffer
        ///
        /// Graphics buffer could be index/vertex buffer or
        /// constant buffer.
        /// It could be used in cpu and/or gpu
        // template<typename T>
        class D3D11Texture : public Texture
        {
            public:
                /// \brief brief constructor description.
                D3D11Texture();

                /// class variable description
                // int public_variable_;

            public:
                /// \brief A brief function description.
                ///
                /// \param p1 Description for p1.
                /// \param p2 Description for p2.
                /// \return Description for return value.
        };
    }  // namespace Rendering

}  // namespace vEngine

#endif /* _VENGINE_RENDERING_D3D11_TEXTURE_HPP */
