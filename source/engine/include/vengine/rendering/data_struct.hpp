#ifndef _VENGINE_RENDERING_DATA_STRUCT_HPP
#define _VENGINE_RENDERING_DATA_STRUCT_HPP

#pragma once

#include <vector>
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
            // similar design https://docs.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_usage
            GBU_CPU_GPU_ReadWrite,
            GPU_CPU_Write_GPU_Read,
            GBU_GPU_Read_Only,
            GBU_GPU_ReadWrite,
        };
        enum class ElementTopology
        {
            ET_Undefined,  // for compute buffer or other data buffers that have not topology relations
            ET_PointList,
            ET_LineList,
            ET_TriangleList,
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
        struct ElementLayout
        {
                struct Element
                {
                        Element(const std::string sematic_name, const DataFormat format) : sematic_name_{sematic_name}, format_{format} {}
                        std::string sematic_name_;
                        DataFormat format_;
                };

                std::vector<Element> elements_;
                ElementTopology topology;
        };
        struct GraphicsBufferDescriptor
        {
                GraphicsBufferType type;
                GraphicsBufferUsage usage;
                ElementLayout layout;
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

        struct PipelineStateDescriptor
        {
                // similar design as https://docs.microsoft.com/en-us/windows/win32/api/d3d12/ns-d3d12-d3d12_graphics_pipeline_state_desc
                std::string vs_name;
                std::string ps_name;
        };
    }  // namespace Rendering

}  // namespace vEngine

#endif /* _VENGINE_RENDERING_DATA_STRUCT_HPP */
