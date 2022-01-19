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
                void TestFunc();
                void Render() override;
                void CreateRenderWindow(void* hwnd) override;
                void PrintInfo() override;

            private:
                ID3D11Device* d3d_device_;
                ID3D11DeviceContext* d3d_imm_context_;
                D3D_FEATURE_LEVEL d3d_feature_level_;
                IDXGISwapChain* d3d_swap_chain_;
                ID3D11RenderTargetView* backbuffer;  // global declaration
        };

    }  // namespace Rendering
}  // namespace vEngine

#endif /* _VENGINE_RENDERING_D3D11_RENDER_ENGINE_HPP */
