/// \file d3d11_graphics_buffer.hpp
/// \brief Head file for D3D11GraphicsBuffer
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_RENDERING_D3D11_GRAPHICS_BUFFER_HPP
#define _VENGINE_RENDERING_D3D11_GRAPHICS_BUFFER_HPP

#pragma once

#include <vengine/rendering/d3d11_predeclear.hpp>
#include <vengine/rendering/graphics_buffer.hpp>

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
        class D3D11GraphicsBuffer : public GraphicsBuffer
        {
            public:
                /// \brief brief constructor description.
                D3D11GraphicsBuffer(const GraphicsBufferDescriptor& desc);

                /// class variable description
                // int public_variable_;

            protected:
                GPUSubresource DoMap() override;
                void DoUnmap() override;

            public:
                ComPtr<ID3D11Buffer> buffer_;
            
                /// \brief A brief function description.
                ///
                /// \param p1 Description for p1.
                /// \param p2 Description for p2.
                /// \return Description for return value.
        };
    }  // namespace Rendering

}  // namespace vEngine

#endif /* _VENGINE_RENDERING_D3D11_GRAPHICS_BUFFER_HPP */
