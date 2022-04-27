
/// \file d3d11_graphics_buffer.cpp
/// \brief source file for D3D11 GraphicsBuffer
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/rendering/d3d11_graphics_buffer.hpp>
#include <vengine/core/context.hpp>
#include <vengine/rendering/d3d11_render_engine.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Rendering
    {
        static D3D11_BIND_FLAG ToD3DBindFlag(GraphicsBufferType type)
        {
            switch (type)
            {
                case GraphicsBufferType::GBT_Index:
                    return D3D11_BIND_INDEX_BUFFER;
                case GraphicsBufferType::GBT_Vertex:
                    return D3D11_BIND_VERTEX_BUFFER;
                default: return D3D11_BIND_UNORDERED_ACCESS;
            }
        }
        static uint32_t ToD3DAccessFlag(GraphicsBufferUsage usage)
        {
            switch (usage)
            {
                case GraphicsBufferUsage::GBU_CPU_GPU_ReadWrite:
                    return D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
                case GraphicsBufferUsage::GPU_CPU_Write_GPU_Read:
                    return D3D11_CPU_ACCESS_WRITE;
                default: return 0;
            }
        }

        static D3D11_USAGE ToD3DUsage(GraphicsBufferUsage usage)
        {
            switch (usage)
            {
                case GraphicsBufferUsage::GBU_CPU_GPU_ReadWrite:
                    return D3D11_USAGE_STAGING;
                case GraphicsBufferUsage::GPU_CPU_Write_GPU_Read:
                    return D3D11_USAGE_DYNAMIC;
                case GraphicsBufferUsage::GBU_GPU_Read_Only:
                    return D3D11_USAGE_IMMUTABLE;
                case GraphicsBufferUsage::GBU_GPU_ReadWrite://but can be update by UpdateSubresource
                    return D3D11_USAGE_DEFAULT;
                default: return D3D11_USAGE_DEFAULT;
            }
        }
        /// constructor detailed defintion,
        /// should be 2 lines
        D3D11GraphicsBuffer::D3D11GraphicsBuffer(const GraphicsBufferDescriptor& desc) : GraphicsBuffer(desc)
        {
            PRINT("D3DGraphicsBuffer");
            auto re = &Core::Context::GetInstance().GetRenderEngine();
            auto d3d_re = dynamic_cast<D3D11RenderEngine*>(re);
            auto device = d3d_re->Device();
            D3D11_BUFFER_DESC d3d_desc;
            d3d_desc.ByteWidth = static_cast<uint32_t>(desc.total_size);
            d3d_desc.StructureByteStride = desc.stride;
            d3d_desc.Usage = ToD3DUsage(desc.usage);
            d3d_desc.BindFlags = ToD3DBindFlag(desc.type);
            d3d_desc.CPUAccessFlags = ToD3DAccessFlag(desc.usage);
            d3d_desc.MiscFlags = 0;

            D3D11_SUBRESOURCE_DATA sub;
            sub.pSysMem = desc.data;
            sub.SysMemPitch = 0;
            sub.SysMemSlicePitch = 0;

            auto hr = device->CreateBuffer(&d3d_desc, &sub, this->buffer_.GetAddressOf());
            if(FAILED(hr))
            {
                PRINT_AND_BREAK("Cannot create buffer");
            }
        }


        void ConstantBuffer()
        {
            //create with usage and access
            // D3D11_USAGE usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
            // D3D11_CPU_ACCESS_FLAG access = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
            //update with map/unmap
            // D3D11_MAP map = D3D11_MAP::D3D11_MAP_WRITE_DISCARD;

        }

        /// A detailed function description, it
        /// should be 2 lines at least.
        // int MyClass::GetVariable(int p1, float p2)
        // {
        //     UNUSED_PARAMETER(p1);
        //     UNUSED_PARAMETER(p2);
        //     return 1;
        // }
    }  // namespace Rendering
}  // namespace vEngine