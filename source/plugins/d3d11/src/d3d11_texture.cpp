
/// \file d3d11_texture.cpp
/// \brief source file for D3D11 Texture
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/rendering/d3d11_texture.hpp>
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
        D3D11Texture::D3D11Texture(const TextureDescriptor& desc) : Texture(desc)
        {
            auto re = &Core::Context::GetInstance().GetRenderEngine();
            auto d3d_re = dynamic_cast<D3D11RenderEngine*>(re);
            auto device = d3d_re->Device();
            // device->CreateTexture2D();
        }
        D3D11Texture::D3D11Texture(ComPtr<ID3D11Texture2D> backBuffer) : Texture(TextureDescriptor::Default())
        {
            D3D11_TEXTURE2D_DESC d3d_desc;
            backBuffer->GetDesc(&d3d_desc);

            this->descriptor_.dimension = TextureDimension::TD_2D;
            this->descriptor_.format = D3D11RenderEngine::D3DFormatToDataFormat(d3d_desc.Format);
            // this->descriptor_.format = D3D11RenderEngine::D3DFormatToDataFormat(d3d_desc.Format);

            this->tex2D_ = backBuffer;
        }

        ComPtr<ID3D11RenderTargetView> D3D11Texture::AsRTV()
        {
            if (this->rt_view_ == nullptr)
            {
                auto re = &Core::Context::GetInstance().GetRenderEngine();
                auto d3d_re = dynamic_cast<D3D11RenderEngine*>(re);
                auto device = d3d_re->Device();

                device->CreateRenderTargetView(this->tex2D_.Get(), nullptr, this->rt_view_.GetAddressOf());
            }
            return this->rt_view_;
        }
        ComPtr<ID3D11DepthStencilView> D3D11Texture::AsDSV()
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