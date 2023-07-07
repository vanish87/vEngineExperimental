/// \file data_struct.hpp
/// \brief Head file for Rendering Data
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_RENDERING_DATA_STRUCT_HPP
#define _VENGINE_RENDERING_DATA_STRUCT_HPP

#pragma once

#include <vector>
#include <unordered_map>
#include <filesystem>
#include <vengine/rendering/data_format.hpp>
#include <vengine/data/meta.hpp>

namespace vEngine
{
    namespace Rendering
    {
        enum class ShaderType
        {
            VertexShader,
            HullShader,
            TessellatorShader,
            DomainShader,
            GeometryShader,
            PixelShader,
            ComputeShader,
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
                constexpr static auto properties()
                {
                    return std::make_tuple(
                        // Core::property("shaders", &PipelineStateDescriptor::shaders)
                        // Core::property("rasterizer", &RasterizerDescriptor::fill_mode),
                        // Core::property("depth_stencil", &RasterizerDescriptor::cull_mode)
                        Core::property("depth_bias", &RasterizerDescriptor::depth_bias));
                };
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
                constexpr static auto properties()
                {
                    return std::make_tuple(
                        // Core::property("shaders", &PipelineStateDescriptor::shaders)
                        // Core::property("rasterizer", &RasterizerDescriptor::fill_mode),
                        // Core::property("depth_stencil", &RasterizerDescriptor::cull_mode)
                        Core::property("depth_enabled", &DepthStencilDescriptor::depth_enabled));
                };
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
                uint32_t offset = 0;
                uint32_t stride = 0; // size of individual element
                uint64_t count = 0;  // the number of element

                //can be calculated from parameters above
                uint32_t pitch = 0;  // use for texture, which is the size of one row in texture
                uint64_t total_byte_size = 0; // total data size
                void* data = nullptr;
                constexpr static auto properties()
                {
                    return std::make_tuple(
                        Core::property("offset", &GPUSubResource::offset), 
                        Core::property("stride", &GPUSubResource::stride), 
                        Core::property("count", &GPUSubResource::count), 
                    );
                };
        };
        struct TextureDescriptor
        {
                constexpr static auto properties()
                {
                    return std::make_tuple(
                        Core::property("dimension", &TextureDescriptor::dimension), 
                        Core::property("width", &TextureDescriptor::width), 
                        Core::property("height", &TextureDescriptor::height),
                        Core::property("depth", &TextureDescriptor::depth),
                        Core::property("format", &TextureDescriptor::format),
                        Core::property("type", &TextureDescriptor::type),
                        Core::property("usage", &TextureDescriptor::usage),
                        Core::property("raw_data", &TextureDescriptor::raw_data)
                    );
                };
                TextureDimension dimension;
                uint32_t width;
                uint32_t height;
                uint32_t depth;
                DataFormat format;
                GraphicsResourceType type;
                GraphicsResourceUsage usage;
                std::vector<uint8_t> raw_data;

                GPUSubResource resource;
                GraphicsBufferSlot slot;

                // std::vector<byte> raw_data;

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
                constexpr static auto properties()
                {
                    return std::tuple_cat(
                        // GameObject::properties(),
                        std::make_tuple(
                            // Core::property("shaders", &PipelineStateDescriptor::shaders)
                            Core::property("type", &GraphicsBufferDescriptor::type)));
                            // Core::property("usage", &GraphicsBufferDescriptor::usage)));
                };
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
                constexpr static auto properties()
                {
                    return std::tuple_cat(
                        // GameObject::properties(),
                        std::make_tuple(
                            // Core::property("shaders", &PipelineStateDescriptor::shaders)
                            Core::property("rasterizer", &PipelineStateDescriptor::rasterizer_descriptor), 
                            Core::property("depth_stencil", &PipelineStateDescriptor::depth_stencil_descriptor)));
                };
                // similar design as https://docs.microsoft.com/en-us/windows/win32/api/d3d12/ns-d3d12-d3d12_graphics_pipeline_state_desc
                // std::unordered_map<ShaderType, std::filesystem::path> shaders;
                RasterizerDescriptor rasterizer_descriptor;
                DepthStencilDescriptor depth_stencil_descriptor;
                static const PipelineStateDescriptor& Default()
                {
                    static PipelineStateDescriptor desc;
                    return desc;
                }
        };

    }  // namespace Rendering

}  // namespace vEngine

#endif /* _VENGINE_RENDERING_DATA_STRUCT_HPP */
