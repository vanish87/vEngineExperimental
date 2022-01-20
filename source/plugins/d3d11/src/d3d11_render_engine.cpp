#include <vengine/core/window.hpp>
#include <vengine/core/application.hpp>
#include <vengine/core/context.hpp>
#include <vengine/rendering/d3d11_render_engine.hpp>

#include <vengine/core/vector.hpp>

#include <d3dcompiler.h>


namespace vEngine
{
    namespace Rendering
    {
        using namespace vEngine::Core;
        using namespace vEngine::Math;


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

            auto hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &scd, &d3d_swap_chain_, &d3d_device_, nullptr, &d3d_imm_context_);

            CHECK_ASSERT(hr == S_OK);
            CHECK_ASSERT_NOT_NULL(d3d_swap_chain_);
            CHECK_ASSERT_NOT_NULL(d3d_device_);
            CHECK_ASSERT_NOT_NULL(d3d_imm_context_);

            // get the address of the back buffer
            ID3D11Texture2D* pBackBuffer;
            hr = d3d_swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
            CHECK_ASSERT(hr == S_OK);

            // use the back buffer address to create the render target
            hr = d3d_device_->CreateRenderTargetView(pBackBuffer, nullptr, &this->backbuffer_);
            CHECK_ASSERT(hr == S_OK);
            pBackBuffer->Release();

            // set the render target as the back buffer
            d3d_imm_context_->OMSetRenderTargets(1, &this->backbuffer_, nullptr);

            // Set the viewport
            D3D11_VIEWPORT viewport;
            ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

            viewport.TopLeftX = 0;
            viewport.TopLeftY = 0;
            viewport.Width = static_cast<FLOAT>(width);
            viewport.Height = static_cast<FLOAT>(height);

            d3d_imm_context_->RSSetViewports(1, &viewport);


            this->InitPipline();
        }
        void D3D11RenderEngine::Update()
        {
            const float color[4] = {0.0f, 0.2f, 0.4f, 1.0f};
            this->d3d_imm_context_->ClearRenderTargetView(this->backbuffer_, color);
            this->TriangleDraw();
            this->d3d_swap_chain_->Present(0, 0);
        }
        void D3D11RenderEngine::Deinit()
        {
            this->DeinitPipline();

            this->d3d_device_->Release();
            this->d3d_swap_chain_->Release();
            this->d3d_imm_context_->Release();
        }
        void D3D11RenderEngine::PrintInfo()
        {
            std::cout << "D3D11" << std::endl;
        }
        static const std::string shader =
            "struct vs_in {\
                float3 position : POSITION;\
                float4 color : COLOR;\
            };\
            struct vs_out {\
                float4 position : SV_POSITION; \
                float4 color : COLOR;\
            };\
            vs_out vs_main(vs_in input) {\
                vs_out output = (vs_out)0; \
                output.position = float4(input.position,1);\
                output.color = input.color;\
                return output;\
            }\
            float4 ps_main(vs_out input) : SV_TARGET {\
                return input.color;\
            }";
        struct VERTEX
        {
                float X, Y, Z;  // position
                float Color[4];   // color
        };
        void D3D11RenderEngine::InitPipline()
        {
            auto hr = D3DCompile(shader.c_str(), shader.length(), nullptr, nullptr, nullptr, "vs_main", "vs_5_0", 0, 0, &vs_blob, nullptr);
            CHECK_ASSERT(hr == S_OK);
            hr = D3DCompile(shader.c_str(), shader.length(), nullptr, nullptr, nullptr, "ps_main", "ps_5_0", 0, 0, &ps_blob, nullptr);
            CHECK_ASSERT(hr == S_OK);

            hr = this->d3d_device_->CreateVertexShader(this->vs_blob->GetBufferPointer(), this->vs_blob->GetBufferSize(), nullptr, &this->vs);
            CHECK_ASSERT(hr == S_OK);
            hr = this->d3d_device_->CreatePixelShader(this->ps_blob->GetBufferPointer(), this->ps_blob->GetBufferSize(), nullptr, &this->ps);
            CHECK_ASSERT(hr == S_OK);

            this->d3d_imm_context_->VSSetShader(this->vs, 0, 0);
            this->d3d_imm_context_->PSSetShader(this->ps, 0, 0);

            D3D11_INPUT_ELEMENT_DESC input_desc[] = 
            {
                {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
                {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
            };

            hr = this->d3d_device_->CreateInputLayout(input_desc, 2, this->vs_blob->GetBufferPointer(), this->vs_blob->GetBufferSize(), &this->layout);
            CHECK_ASSERT(hr == S_OK);

            this->d3d_imm_context_->IASetInputLayout(this->layout);

            // create a triangle using the VERTEX struct
            VERTEX OurVertices[] = 
            {
                {0.0f, 0.5f, 0.0f,    {1.0f, 0.0f, 0.0f, 1.0f}}, 
                {0.45f, -0.5, 0.0f,   {0.0f, 1.0f, 0.0f, 1.0f}}, 
                {-0.45f, -0.5f, 0.0f, {0.0f, 0.0f, 1.0f, 1.0f}}
            };

            // create the vertex buffer
            D3D11_BUFFER_DESC bd;
            ZeroMemory(&bd, sizeof(bd));

            bd.Usage = D3D11_USAGE_DYNAMIC;              // write access access by CPU and GPU
            bd.ByteWidth = sizeof(VERTEX) * 3;           // size is the VERTEX struct * 3
            bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;     // use as a vertex buffer
            bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;  // allow CPU to write in buffer

            hr = this->d3d_device_->CreateBuffer(&bd, NULL, &this->vertex_buffer);  // create the buffer
            CHECK_ASSERT(hr == S_OK);

            // copy the vertices into the buffer
            D3D11_MAPPED_SUBRESOURCE ms;
            this->d3d_imm_context_->Map(this->vertex_buffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);  // map the buffer
            memcpy(ms.pData, OurVertices, sizeof(OurVertices));                                          // copy the data
            this->d3d_imm_context_->Unmap(this->vertex_buffer, NULL);                                    // unmap the buffer
        }
        void D3D11RenderEngine::TriangleDraw()
        {
            // select which vertex buffer to display
            UINT stride = sizeof(VERTEX);
            UINT offset = 0;
            this->d3d_imm_context_->IASetVertexBuffers(0, 1, &this->vertex_buffer, &stride, &offset);

            // select which primtive type we are using
            this->d3d_imm_context_->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

            // draw the vertex buffer to the back buffer
            this->d3d_imm_context_->Draw(3, 0);
        }
        void D3D11RenderEngine::DeinitPipline() 
        {
            this->vs_blob->Release();
            this->ps_blob->Release();
            this->vs->Release();
            this->ps->Release();
            this->layout->Release();
            this->vertex_buffer->Release();
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