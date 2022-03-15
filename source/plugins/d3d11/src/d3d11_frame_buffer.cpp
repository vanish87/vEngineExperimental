/// \file d3d11_frame_buffer.cpp
/// \brief source file for D3D11 FrameBuffer
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/rendering/d3d11_frame_buffer.hpp>
#include <vengine/core/context.hpp>
#include <vengine/rendering/d3d11_render_engine.hpp>
#include <vengine/rendering/d3d11_texture.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Rendering
    {
        using namespace vEngine::Core;

        /// constructor detailed defintion,
        /// should be 2 lines
        D3D11FrameBuffer::D3D11FrameBuffer() : FrameBuffer() {}
        D3D11FrameBuffer::D3D11FrameBuffer(TextureSharedPtr backBuffer, const FrameBufferDescriptor& desc) : FrameBuffer()
        {
            UNUSED_PARAMETER(desc);
            // auto& re = Context::GetInstance().GetRenderEngine();
            this->colorTextures_.push_back(backBuffer);
        }
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView> D3D11FrameBuffer::GetRenderTargetView()
        {
            if (this->rt_view_ == nullptr)
            {
                auto& re = Context::GetInstance().GetRenderEngine();
                auto d3d_re = dynamic_cast<D3D11RenderEngine*>(&re);
                auto device = d3d_re->Device();
                auto d3d_tex = dynamic_cast<D3D11Texture*>(this->colorTextures_[0].get());


                device->CreateRenderTargetView(d3d_tex->D3DTexture().Get(), nullptr, this->rt_view_.GetAddressOf());
            }

            return this->rt_view_;
        }
        Microsoft::WRL::ComPtr<ID3D11DepthStencilView> D3D11FrameBuffer::GetDepthStencilView()
        {
            return this->ds_view_;
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