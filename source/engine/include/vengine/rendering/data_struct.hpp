#ifndef _VENGINE_RENDERING_DATA_STRUCT_HPP
#define _VENGINE_RENDERING_DATA_STRUCT_HPP

#pragma once

#include <vector>
#include <unordered_map>
#include <filesystem>
#include <vengine/rendering/data_format.hpp>
namespace vEngine
{
    namespace Rendering
    {
        enum class ShaderType
        {
            VS,
            GS,
            PS,
            CS,
        };
        enum class GraphicsResourceType
        {
            Index,
            Vertex,
            CBuffer,
            TextureR,   // Read only texture
            TextureRW,  // as Shader Resource and Render Target
            TextureW,   // as Render Target only
            Depth,
        };

        enum class GraphicsResourceUsage
        {
            // similar design https://docs.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_usage
            CPU_GPU_ReadWrite,
            CPU_Write_GPU_Read,
            GPU_Read_Only,
            GPU_ReadWrite,
        };
        enum class GraphicsBufferSlot : int16_t
        {
            Slot0 = 0,
            Slot1,
            Slot2,
            Slot3,
        };
        enum class ElementTopology
        {
            Undefined,  // for compute buffer or other data buffers that have not topology relations
            PointList,
            LineList,
            TriangleList,
        };
        enum class TextureDimension
        {
            TD_1D,
            TD_2D,
            TD_3D,
            TD_Cube,
        };
        enum class FillMode
        {
            Solid,
            Wireframe,
        };
        enum class CullMode
        {
            None,
            Front,
            Back,
        };
        enum class FrontFacingDirection
        {
            Clockwise,
            CounterClockwise,
        };
        enum class DepthWriteMask
        {
            Zero,  // turn of writes to depth
            All,
        };

        enum class ComparisonFunc
        {
            Never,
            Less,
            Equal,
            LessEqual,
            Greater,
            NotEqual,
            GreatEqual,
            Always,
        };

        struct RasterizerDescriptor
        {
                FillMode fill_mode = FillMode::Solid;
                CullMode cull_mode = CullMode::Back;
                FrontFacingDirection front_facing = FrontFacingDirection::Clockwise;
                int depth_bias = 0;
                float depth_bias_clamp = 0;
                float slop_scaled_depth_bias = 0;
                bool depth_clip_enabled = true;
                bool multisample_enabled = false;
                bool antialiased_line_enabled = false;
                uint16_t forced_sample_count = 0;
        };

        struct DepthStencilDescriptor
        {
                bool depth_enabled = true;
                DepthWriteMask depth_write_mask = DepthWriteMask::All;
                ComparisonFunc comparison_func = ComparisonFunc::Less;
                bool stencil_enabled = false;
                uint8_t stencil_read_mask = 0xff;
                uint8_t stencil_write_mask = 0xff;
        };

        // https://docs.microsoft.com/en-us/windows/win32/direct3d11/how-to--use-dynamic-resources
        struct GPUSubResource
        {
                uint32_t offset;
                uint32_t stride;
                uint32_t pitch;  // use for texture, which is the size of one row in texture
                uint64_t count;
                uint64_t total_size;
                void* data;
        };
        struct TextureDescriptor
        {
                TextureDimension dimension;
                uint32_t width;
                uint32_t height;
                uint32_t depth;
                DataFormat format;
                GraphicsResourceType type;
                GraphicsResourceUsage usage;

                GPUSubResource resource;
                GraphicsBufferSlot slot;

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
                GraphicsResourceType type;
                GraphicsResourceUsage usage;
                ElementLayout layout;
                // DataFormat format;// undefined format for compute buffer
                // std::vector<std::pair<

                GPUSubResource resource;
                GraphicsBufferSlot slot;
        };

        struct FrameBufferDescriptor
        {
                uint32_t width;
                uint32_t height;
                DataFormat colorFormat;
                DataFormat depthStencilFormat;
                GraphicsResourceUsage usage;
                // TextureUsage usage;
                // std::vector<std::pair<
        };

        struct PipelineStateDescriptor
        {
                // similar design as https://docs.microsoft.com/en-us/windows/win32/api/d3d12/ns-d3d12-d3d12_graphics_pipeline_state_desc
                std::unordered_map<ShaderType, std::filesystem::path> shaders;
                RasterizerDescriptor rasterizer_descriptor;
                DepthStencilDescriptor depth_stencil_descriptor;
        };

        struct Shader
        {
                std::filesystem::path path;
                std::vector<char> content;
                Shader(const std::filesystem::path path) : path{path} {};
        };
    }  // namespace Rendering

}  // namespace vEngine

#endif /* _VENGINE_RENDERING_DATA_STRUCT_HPP */
