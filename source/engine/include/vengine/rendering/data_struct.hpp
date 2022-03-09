#ifndef _VENGINE_RENDERING_DATA_STRUCT_HPP
#define _VENGINE_RENDERING_DATA_STRUCT_HPP

#include <vengine/rendering/data_format.hpp>

namespace vEngine
{
    namespace Rendering
    {
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
        enum class TextureDimension
        {
            TD_1D,
            TD_2D,
            TD_3D,
            TD_Cure,

        };
        enum class TextureUsage
        {
            GBU_CPU = 1 << 0,
            GBU_GPU = 1 << 1,
        };
        struct TextureDescriptor
        {
                TextureDimension dimension;
                DataFormat format;
                TextureUsage usage;
                // std::vector<std::pair<
        };
        struct GraphicsBufferDescriptor
        {
                GraphicsBufferType type;
                GraphicsBufferUsage usage;
                // std::vector<std::pair<

                int offset;
                int stride;
        };
        struct FrameBufferDescriptor
        {
                // DataFormat format;
                // TextureUsage usage;
                // std::vector<std::pair<
        };

    }  // namespace Rendering

}  // namespace vEngine

#endif /* _VENGINE_RENDERING_DATA_STRUCT_HPP */
