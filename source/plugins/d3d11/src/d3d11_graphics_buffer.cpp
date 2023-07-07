
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

        /// constructor detailed defintion,
        /// should be 2 lines
        D3D11GraphicsBuffer::D3D11GraphicsBuffer(const GraphicsBufferDescriptor& desc) : GraphicsBuffer(desc)
        {
            PRINT("D3DGraphicsBuffer");
            auto& re = Core::Context::GetInstance().GetRenderEngine();
            auto d3d_re = dynamic_cast<D3D11RenderEngine*>(re.get());
            auto device = d3d_re->Device();
            D3D11_BUFFER_DESC d3d_desc;
            d3d_desc.ByteWidth = static_cast<uint32_t>(desc.resource.total_byte_size);
            d3d_desc.StructureByteStride = desc.resource.stride;
            d3d_desc.Usage = D3D11RenderEngine::ToD3DUsage(desc.usage);
            d3d_desc.BindFlags = D3D11RenderEngine::ToD3DBindFlag(desc.type);
            d3d_desc.CPUAccessFlags = D3D11RenderEngine::ToD3DAccessFlag(desc.usage);
            d3d_desc.MiscFlags = 0;

            D3D11_SUBRESOURCE_DATA sub;
            sub.pSysMem = desc.resource.data;
            sub.SysMemPitch = 0;
            sub.SysMemSlicePitch = 0;

            auto hr = device->CreateBuffer(&d3d_desc, &sub, this->buffer_.GetAddressOf());
            if (FAILED(hr))
            {
                PRINT_AND_BREAK("Cannot create buffer");
            }
        }

        GPUSubResource D3D11GraphicsBuffer::DoMap()
        {
            auto& re = Core::Context::GetInstance().GetRenderEngine();
            auto d3d_re = dynamic_cast<D3D11RenderEngine*>(re.get());
            auto context = d3d_re->DeviceContext();

            GPUSubResource sub;
            D3D11_MAPPED_SUBRESOURCE data;

            auto hr = context->Map(this->buffer_.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
            if (FAILED(hr))
            {
                PRINT_AND_BREAK("Cannot Map buffer");
            }
            sub.data = data.pData;
            return sub;
        }
        void D3D11GraphicsBuffer::DoUnmap()
        {
            auto& re = Core::Context::GetInstance().GetRenderEngine();
            auto d3d_re = dynamic_cast<D3D11RenderEngine*>(re.get());
            auto context = d3d_re->DeviceContext();
            context->Unmap(this->buffer_.Get(), 0);
        }

        void ConstantBuffer()
        {
            // create with usage and access
            //  D3D11_USAGE usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
            //  D3D11_CPU_ACCESS_FLAG access = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
            // update with map/unmap
            //  D3D11_MAP map = D3D11_MAP::D3D11_MAP_WRITE_DISCARD;
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