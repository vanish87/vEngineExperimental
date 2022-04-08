/// \file graphics_buffer.hpp
/// \brief Head file for Graphics Buffer
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_RENDERING_GRAPHICS_BUFFER_HPP
#define _VENGINE_RENDERING_GRAPHICS_BUFFER_HPP

#include <VENGINE_API.h>
#include <engine.hpp>

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
        class VENGINE_API GraphicsBuffer
        {
            public:
                /// \brief brief constructor description.
                GraphicsBuffer(const GraphicsBufferDescriptor& desc);
                virtual ~GraphicsBuffer();

                /// class variable description
                // int public_variable_;

				GraphicsBufferDescriptor descriptor_;

            public:
                /// \brief A brief function description.
                ///
                /// \param p1 Description for p1.
                /// \param p2 Description for p2.
                /// \return Description for return value.
        };
    }  // namespace Rendering

}  // namespace vEngine

#endif /* _VENGINE_RENDERING_GRAPHICS_BUFFER_HPP */
