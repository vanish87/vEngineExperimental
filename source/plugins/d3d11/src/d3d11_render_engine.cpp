#include <vengine/rendering/d3d11_render_engine.hpp>

namespace vEngine
{
    namespace Rendering
    {

        void D3D11RenderEngine::TestFunc() {}

        void D3D11RenderEngine::CreateRenderWindow(void* hwnd, int width, int height)
        {
            DXGI_SWAP_CHAIN_DESC scd;

            // clear out the struct for use
            ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

            // fill the swap chain description struct
            scd.BufferCount = 1;                                 // one back buffer
            scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // use 32-bit color
            scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;   // how swap chain is to be used
            scd.OutputWindow = static_cast<HWND>(hwnd);          // the window to be used
            scd.SampleDesc.Count = 4;                            // how many multisamples
            scd.Windowed = true;                                 // windowed/full-screen mode

            D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, &scd, &d3d_swap_chain_, &d3d_device_, NULL, &d3d_imm_context_);

            auto w = width;
            auto h = height;
            HRESULT result = d3d_swap_chain_->ResizeBuffers(1, w, h, DXGI_FORMAT_R8G8B8A8_UNORM, 0);

            UNUSED_PARAMETER(result);

            // get the address of the back buffer
            ID3D11Texture2D* pBackBuffer;
            d3d_swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

            // use the back buffer address to create the render target
            d3d_device_->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
            pBackBuffer->Release();

            // set the render target as the back buffer
            d3d_imm_context_->OMSetRenderTargets(1, &backbuffer, NULL);

            // Set the viewport
            D3D11_VIEWPORT viewport;
            ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

            viewport.TopLeftX = 0;
            viewport.TopLeftY = 0;
            viewport.Width = static_cast<FLOAT>(w);
            viewport.Height = static_cast<FLOAT>(h);

            d3d_imm_context_->RSSetViewports(1, &viewport);
        }
        void D3D11RenderEngine::Render() {}
        void D3D11RenderEngine::PrintInfo()
        {
            std::cout << "D3D11" << std::endl;
        }

    }  // namespace Rendering
}  // namespace vEngine

extern "C" {
    void CreateRenderEngine(std::unique_ptr<vEngine::Rendering::RenderEngine>& ptr)
    {
        ptr = std::make_unique<vEngine::Rendering::D3D11RenderEngine>();
    }
    void DestoryRenderEngine(std::unique_ptr<vEngine::Rendering::RenderEngine>& ptr)
    {
        ptr.reset();
    }
}