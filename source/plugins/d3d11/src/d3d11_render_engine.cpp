#include <vengine/core/window.hpp>
#include <vengine/core/application.hpp>
#include <vengine/core/context.hpp>
#include <vengine/rendering/d3d11_render_engine.hpp>

namespace vEngine
{
    namespace Rendering
    {
        using namespace vEngine::Core;

        void D3D11RenderEngine::Init()
        {
            // TODO Use IDXGIFactory to check adapters

            const auto config = Context::GetInstance().CurrentConfigure();
            auto window = Context::GetInstance().AppInstance().CurrentWindow();
            auto hwnd = static_cast<HWND>(window->WindowHandle());
            auto width = config.graphics_configure.width;
            auto height = config.graphics_configure.height;

            DXGI_SWAP_CHAIN_DESC scd;
            // clear out the struct for use
            ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

            // fill the swap chain description struct
            scd.BufferCount = 1;  // one back buffer
            scd.BufferDesc.Width = width;
            scd.BufferDesc.Height = height;
            scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // use 32-bit color
            scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;   // how swap chain is to be used
            scd.OutputWindow = hwnd;                             // the window to be used
            scd.SampleDesc.Count = 1;                            // how many multisamples
            scd.Windowed = true;                                 // windowed/full-screen mode

            auto hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, &scd, &d3d_swap_chain_, &d3d_device_, NULL, &d3d_imm_context_);

            CHECK_ASSERT(hr == S_OK);
            CHECK_ASSERT_NOT_NULL(d3d_swap_chain_);
            CHECK_ASSERT_NOT_NULL(d3d_device_);
            CHECK_ASSERT_NOT_NULL(d3d_imm_context_);

            // get the address of the back buffer
            ID3D11Texture2D* pBackBuffer;
            hr = d3d_swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
            CHECK_ASSERT(hr == S_OK);

            // use the back buffer address to create the render target
            hr = d3d_device_->CreateRenderTargetView(pBackBuffer, NULL, &this->backbuffer_);
            CHECK_ASSERT(hr == S_OK);
            pBackBuffer->Release();

            // set the render target as the back buffer
            d3d_imm_context_->OMSetRenderTargets(1, &this->backbuffer_, NULL);

            // Set the viewport
            D3D11_VIEWPORT viewport;
            ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

            viewport.TopLeftX = 0;
            viewport.TopLeftY = 0;
            viewport.Width = static_cast<FLOAT>(width);
            viewport.Height = static_cast<FLOAT>(height);

            d3d_imm_context_->RSSetViewports(1, &viewport);
        }
        void D3D11RenderEngine::Update() 
        {
            const float color[4] = {0.0f, 0.2f, 0.4f, 1.0f};
            this->d3d_imm_context_->ClearRenderTargetView(this->backbuffer_, color);
            this->d3d_swap_chain_->Present(0, 0);
        }
        void D3D11RenderEngine::Deinit() 
        {
            this->d3d_device_->Release();
            this->d3d_swap_chain_->Release();
            this->d3d_imm_context_->Release();
        }
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