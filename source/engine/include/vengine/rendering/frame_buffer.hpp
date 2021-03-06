/// \file frame_buffer.hpp
/// \brief Head file for Frame Buffer
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_RENDERING_FRAME_BUFFER_HPP
#define _VENGINE_RENDERING_FRAME_BUFFER_HPP

#include <VENGINE_API.h>

#include <engine.hpp>
#include <vector>

namespace vEngine
{
    namespace Rendering
    {
        using namespace Core;

        /// \brief Unity-like Graphics buffer
        ///
        /// Graphics buffer could be index/vertex buffer or
        /// constant buffer.
        /// It could be used in cpu and/or gpu
        // template<typename T>
        class VENGINE_API FrameBuffer
        {
            public:
                /// \brief brief constructor description.
                FrameBuffer(const FrameBufferDescriptor& desc);
                FrameBuffer(TextureSharedPtr backBuffer, const FrameBufferDescriptor& desc);
                virtual ~FrameBuffer();

                TextureSharedPtr GetColor(const uint8_t index)
                {
                    return this->colorTextures_[index];
                }
                TextureSharedPtr GetDepthStencil()
                {
                    return this->depthStencilTexture_;
                };

                /// class variable description
                // int public_variable_;

                FrameBufferDescriptor descriptor_;

            public:
                /// \brief A brief function description.
                ///
                /// \param p1 Description for p1.
                /// \param p2 Description for p2.
                /// \return Description for return value.
                std::vector<TextureSharedPtr> colorTextures_;
                TextureSharedPtr depthStencilTexture_;

                // view matrix and projection matrix
                //per frame cbuffer: lights
                //per camera cbuffer: view proj, pos, rt demensions
                //per object: world matrix, dynamic material properties
                //per material: shadred properties

                //not used for now
                //maybe rt dimensions
                GraphicsBufferSharedPtr frame_constat_buffer_;
        };
    }  // namespace Rendering

}  // namespace vEngine

#endif /* _VENGINE_RENDERING_FRAME_BUFFER_HPP */
