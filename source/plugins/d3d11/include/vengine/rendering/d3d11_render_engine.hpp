#ifndef _VENGINE_RENDERING_D3D11_RENDER_ENGINE_HPP
#define _VENGINE_RENDERING_D3D11_RENDER_ENGINE_HPP
#pragma once

#include <d3d11.h>

#include <vengine/rendering/render_engine.hpp>
namespace vEngine
{
    namespace Rendering
    {
        class D3D11RenderEngine : public RenderEngine
        {
            public:
                D3D11RenderEngine()
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

                TextureSharedPtr Create(const TextureDescriptor& desc) override;

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
                ID3D11Device* d3d_device_;
                ID3D11DeviceContext* d3d_imm_context_;
                IDXGISwapChain* d3d_swap_chain_;
                ID3D11RenderTargetView* backbuffer_; 
        };

    }  // namespace Rendering
}  // namespace vEngine

#endif /* _VENGINE_RENDERING_D3D11_RENDER_ENGINE_HPP */
