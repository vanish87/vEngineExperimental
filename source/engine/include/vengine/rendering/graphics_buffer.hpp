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
		enum class DataFormat
		{
			DF_RGB32Float,
			DF_R32Int,
		};
		enum class GraphicsBufferType
		{
			GBT_Index,
			GBT_Vertex,
		};

		enum class GraphicsBufferUsage
		{
			GBU_CPU = 1 << 0,
			GBU_GPU = 1 << 1,
		};
		enum class GraphicsBufferTopology
		{
			GBT_Undefined,
			GBT_PointList,
			GBT_LineList,
			GBT_TriangleList,
		};
		class GraphicsBufferDescriptor
		{
			GraphicsBufferType type;
			GraphicsBufferUsage usage;
			// std::vector<std::pair<

			int offset;
			int stride;
		};
        /// \brief Unity-like Graphics buffer
        ///
        /// Graphics buffer could be index/vertex buffer or
		/// constant buffer.
		/// It could be used in cpu and/or gpu
		// template<typename T>
        class GraphicsBuffer
        {
            public:
                /// \brief brief constructor description.
                GraphicsBuffer(){};

                /// class variable description
                // int public_variable_;

				GraphicsBufferDescriptor descriptor_;

            public:
                /// \brief A brief function description.
                ///
                /// \param p1 Description for p1.
                /// \param p2 Description for p2.
                /// \return Description for return value.
                static GraphicsBuffer Create(const GraphicsBufferDescriptor& desc)
				{
					UNUSED_PARAMETER(desc);
					return GraphicsBuffer();
				}
        };
    }  // namespace Rendering

}  // namespace vEngine

#endif /* _VENGINE_RENDERING_GRAPHICS_BUFFER_HPP */
