
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
        D3D11Texture::D3D11Texture(const TextureDescriptor& desc) : Texture(desc) {}
        void D3D11Texture::PrepareData()
        {
            if (this->tex2D_ == nullptr)
            {
                auto& re = Core::Context::GetInstance().GetRenderEngine();
                auto d3d_re = dynamic_cast<D3D11RenderEngine*>(re.get());
                auto device = d3d_re->Device();
                auto desc = this->descriptor_;
                switch (desc.dimension)
                {
                    case TextureDimension::TD_1D:
                        break;
                    case TextureDimension::TD_2D:
                    {
                        D3D11_TEXTURE2D_DESC d3d_desc;
                        d3d_desc.Width = desc.width;
                        d3d_desc.Height = desc.height;
                        d3d_desc.Format = D3D11RenderEngine::ToD3DFormat(desc.format);
                        d3d_desc.Usage = D3D11RenderEngine::ToD3DUsage(desc.usage);
                        d3d_desc.CPUAccessFlags = D3D11RenderEngine::ToD3DAccessFlag(desc.usage);
                        d3d_desc.BindFlags = D3D11RenderEngine::ToD3DBindFlag(desc.type);

                        d3d_desc.ArraySize = 1;
                        d3d_desc.MipLevels = 1;
                        d3d_desc.MiscFlags = 0;
                        d3d_desc.SampleDesc.Count = 1;
                        d3d_desc.SampleDesc.Quality = 0;

                        D3D11_SUBRESOURCE_DATA init_data;
                        init_data.pSysMem = desc.resource.data;
                        init_data.SysMemPitch = desc.resource.pitch;
                        init_data.SysMemSlicePitch = 0;

                        auto hr = device->CreateTexture2D(&d3d_desc, desc.resource.data == nullptr ? nullptr : &init_data, this->tex2D_.GetAddressOf());
                        if (FAILED(hr))
                        {
                            PRINT_AND_BREAK("Cannot create Texture2D");
                        }
                    }
                    break;
                    case TextureDimension::TD_3D:
                    {
                    }
                    break;
                        break;

                    default:
                        break;
                }
            }
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

        ComPtr<ID3D11ShaderResourceView> D3D11Texture::AsSRV()
        {
            if (this->sr_view_ == nullptr)
            {
                auto& re = Core::Context::GetInstance().GetRenderEngine();
                auto d3d_re = dynamic_cast<D3D11RenderEngine*>(re.get());
                auto device = d3d_re->Device();

                D3D11_SHADER_RESOURCE_VIEW_DESC desc;
                desc.Format = D3D11RenderEngine::ToD3DFormat(this->descriptor_.format);
                desc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;
                desc.Texture2D.MipLevels = 0;
                desc.Texture2D.MostDetailedMip = 0;

                auto hr = device->CreateShaderResourceView(this->tex2D_.Get(), nullptr, this->sr_view_.GetAddressOf());
                CHECK_ASSERT(hr == S_OK);
            }
            return this->sr_view_;
        }
        ComPtr<ID3D11RenderTargetView> D3D11Texture::AsRTV()
        {
            if (this->rt_view_ == nullptr)
            {
                auto& re = Core::Context::GetInstance().GetRenderEngine();
                auto d3d_re = dynamic_cast<D3D11RenderEngine*>(re.get());
                auto device = d3d_re->Device();

                device->CreateRenderTargetView(this->tex2D_.Get(), nullptr, this->rt_view_.GetAddressOf());
            }
            return this->rt_view_;
        }
        ComPtr<ID3D11DepthStencilView> D3D11Texture::AsDSV()
        {
            if (this->ds_view_ == nullptr)
            {
                auto& re = Core::Context::GetInstance().GetRenderEngine();
                auto d3d_re = dynamic_cast<D3D11RenderEngine*>(re.get());
                auto device = d3d_re->Device();

                device->CreateDepthStencilView(this->tex2D_.Get(), nullptr, this->ds_view_.GetAddressOf());
            }
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