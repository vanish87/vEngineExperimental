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

namespace vEngine
{
    namespace Rendering
    {
        /// \brief Unity-like Graphics buffer
        ///
        /// Graphics buffer could be index/vertex buffer or
		/// constant buffer.
		/// It could be used in cpu and/or gpu
        class GraphicsBuffer
        {
            public:
                /// \brief brief constructor description.
                GraphicsBuffer();

                /// class variable description
                // int public_variable_;

            public:
                /// \brief A brief function description.
                ///
                /// \param p1 Description for p1.
                /// \param p2 Description for p2.
                /// \return Description for return value.
                // int Create(int p1, float p2);
        };
    }  // namespace Rendering

}  // namespace vEngine

#endif /* _VENGINE_RENDERING_GRAPHICS_BUFFER_HPP */
