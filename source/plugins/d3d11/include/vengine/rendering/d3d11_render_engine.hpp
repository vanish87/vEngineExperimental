#ifndef _VENGINE_RENDERING_D3D11_RENDER_ENGINE_HPP
#define _VENGINE_RENDERING_D3D11_RENDER_ENGINE_HPP
#pragma once

#include <vengine/rendering/d3d11_predeclear.hpp>
#include <vengine/rendering/render_engine.hpp>
namespace vEngine
{
    namespace Rendering
    {
        class D3D11RenderEngine : public RenderEngine
        {
            public:
                D3D11RenderEngine() : RenderEngine()
                {
                    PRINT("Create D3D11");
                }
                ~D3D11RenderEngine()
                {
                    PRINT("Destructor D3D11");
                }
                void Init() override;
                void Deinit() override;
                void Update() override;
                void PrintInfo() override;

                void OnBind(const FrameBufferSharedPtr FrameBuffer) override;
                PipelineStateSharedPtr OnRegister(const PipelineStateDescriptor& pipeline_desc) override;
                void Render(const GraphicsBufferSharedPtr vertice, const GraphicsBufferSharedPtr indice) override;

                TextureSharedPtr Create(const TextureDescriptor& desc) override;
                FrameBufferSharedPtr Create(const FrameBufferDescriptor& desc) override;
                GraphicsBufferSharedPtr Create(const GraphicsBufferDescriptor& desc) override;

                /// \brief mainly used to create Resource Views(ie. RenderTargetView)
                /// 
                /// \return ComPtr<ID3D11Device> 
                ComPtr<ID3D11Device> Device()
                {
                    return this->d3d_device_;
                }
                ComPtr<ID3D11DeviceContext> DeviceContext()
                {
                    return this->d3d_imm_context_;
                }

                static DataFormat D3DFormatToDataFormat(DXGI_FORMAT formart)
                {
                    switch (formart)
                    {
                        case DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM:
                            return DataFormat::DF_RGBA32;
                        default:
                            break;
                    }

                    return DataFormat::DF_Undifiend;
                }

            private:
                ID3D11InputLayout* layout;
                ID3DBlob* vs_blob;
                ID3DBlob* ps_blob;
                ID3D11VertexShader* vs;
                ID3D11PixelShader* ps;
                ID3D11Buffer* vertex_buffer;

                void InitPipline();
                void DeinitPipline();
                void TriangleDraw();

            private:
                ComPtr<ID3D11Device> d3d_device_;// for create resource/buffer/textures/views
                ComPtr<ID3D11DeviceContext> d3d_imm_context_;  // for draw calls/set state/set buffers
                ComPtr<IDXGISwapChain> d3d_swap_chain_; // for screen buffers
        };

    }  // namespace Rendering
}  // namespace vEngine

#endif /* _VENGINE_RENDERING_D3D11_RENDER_ENGINE_HPP */
