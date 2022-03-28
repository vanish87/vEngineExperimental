
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
            auto re = &Core::Context::GetInstance().GetRenderEngine();
            auto d3d_re = dynamic_cast<D3D11RenderEngine*>(re);
            auto device = d3d_re->Device();
            // D3D11_BUFFER_DESC d3d_desc;
            // device->CreateBuffer(&d3d_desc, nullptr, this->buffer_.GetAddressOf());
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