#ifndef _VENGINE_RENDERING_DATA_STRUCT_HPP
#define _VENGINE_RENDERING_DATA_STRUCT_HPP

#pragma once

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
            //similar design https://docs.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_usage
            GBU_CPU_GPU_ReadWrite,
            GPU_CPU_Write_GPU_Read,
            GBU_GPU_Read,
            GBU_GPU_ReadWrite,
        };
        enum class GraphicsBufferTopology
        {
            GBT_Undefined, // for compute buffer or other data buffers that have not topology relations
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
            TU_CPU = 1 << 0,
            TU_GPU = 1 << 1,
        };
        struct TextureDescriptor
        {
                TextureDimension dimension;
                DataFormat format;
                TextureUsage usage;
                // std::vector<std::pair<

                static const TextureDescriptor& Default()
                {
                    static TextureDescriptor desc;
                    return desc;
                }
        };
        struct GraphicsBufferDescriptor
        {
                GraphicsBufferType type;
                GraphicsBufferUsage usage;
                GraphicsBufferTopology topology;
                // DataFormat format;// undefined format for compute buffer
                // std::vector<std::pair<

                uint32_t offset;
                uint32_t stride;
                uint64_t count;
                uint64_t total_size;
                void* data;
        };
        struct FrameBufferDescriptor
        {
                DataFormat colorFormat;
                DataFormat depthStencilFormat;
                TextureUsage usage;
                // TextureUsage usage;
                // std::vector<std::pair<
        };

    }  // namespace Rendering

}  // namespace vEngine

#endif /* _VENGINE_RENDERING_DATA_STRUCT_HPP */
