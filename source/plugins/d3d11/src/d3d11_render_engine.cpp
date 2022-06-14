#include <d3dcompiler.h>

#include <cstring>
#include <vengine/core/application.hpp>
#include <vengine/core/context.hpp>
#include <vengine/core/vector.hpp>
#include <vengine/core/window.hpp>
#include <vengine/rendering/d3d11_frame_buffer.hpp>
#include <vengine/rendering/d3d11_graphics_buffer.hpp>
#include <vengine/rendering/d3d11_pipeline_state.hpp>
#include <vengine/rendering/d3d11_render_engine.hpp>
#include <vengine/rendering/d3d11_texture.hpp>

namespace vEngine
{
    namespace Rendering
    {
        using namespace vEngine::Core;
        using namespace vEngine::Math;

        uint32_t D3D11RenderEngine::ToD3DBindFlag(GraphicsResourceType type)
        {
            switch (type)
            {
                case GraphicsResourceType::Index:
                    return D3D11_BIND_INDEX_BUFFER;
                case GraphicsResourceType::Vertex:
                    return D3D11_BIND_VERTEX_BUFFER;
                case GraphicsResourceType::CBuffer:
                    return D3D11_BIND_CONSTANT_BUFFER;
                case GraphicsResourceType::TextureR:
                    return D3D11_BIND_SHADER_RESOURCE;
                case GraphicsResourceType::TextureRW:
                    return D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
                case GraphicsResourceType::TextureW:
                    return D3D11_BIND_RENDER_TARGET;
                case GraphicsResourceType::Depth:
                    return D3D11_BIND_DEPTH_STENCIL;
                default:
                    return D3D11_BIND_UNORDERED_ACCESS;
            }
        }
        uint32_t D3D11RenderEngine::ToD3DAccessFlag(GraphicsResourceUsage usage)
        {
            switch (usage)
            {
                case GraphicsResourceUsage::CPU_GPU_ReadWrite:
                    return D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
                case GraphicsResourceUsage::CPU_Write_GPU_Read:
                    return D3D11_CPU_ACCESS_WRITE;
                case GraphicsResourceUsage::GPU_Read_Only:
                    return 0;
                case GraphicsResourceUsage::GPU_ReadWrite:
                    return 0;
                default:
                    return 0;
            }
        }
        D3D11_USAGE D3D11RenderEngine::ToD3DUsage(GraphicsResourceUsage usage)
        {
            switch (usage)
            {
                case GraphicsResourceUsage::CPU_GPU_ReadWrite:
                    return D3D11_USAGE_STAGING;
                case GraphicsResourceUsage::CPU_Write_GPU_Read:
                    return D3D11_USAGE_DYNAMIC;
                case GraphicsResourceUsage::GPU_Read_Only:
                    return D3D11_USAGE_IMMUTABLE;
                case GraphicsResourceUsage::GPU_ReadWrite:  // but can be update by UpdateSubResource
                    return D3D11_USAGE_DEFAULT;
                default:
                    return D3D11_USAGE_DEFAULT;
            }
        }
        DXGI_FORMAT D3D11RenderEngine::ToD3DFormat(DataFormat format)
        {
            switch (format)
            {
                case DataFormat::RGBA32:
                    return DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
                case DataFormat::RGBAFloat:
                    return DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
                case DataFormat::RGBAInt:
                    return DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_SINT;
                case DataFormat::D24U8:
                    return DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
                default:
                    break;
            }
            CHECK_ASSERT(false);
            return DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
        }
        DataFormat D3D11RenderEngine::D3DFormatToDataFormat(DXGI_FORMAT format)
        {
            switch (format)
            {
                case DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM:
                    return DataFormat::RGBA32;
                default:
                    break;
            }

            return DataFormat::Undefined;
        }

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
            CHECK_ASSERT_NOT_NULL(this->d3d_swap_chain_);
            CHECK_ASSERT_NOT_NULL(this->d3d_device_);
            CHECK_ASSERT_NOT_NULL(this->d3d_imm_context_);

            // get the address of the back buffer
            ID3D11Texture2D* pBackBuffer;
            hr = this->d3d_swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
            CHECK_ASSERT(hr == S_OK);

            auto backBufferTexture = std::make_shared<D3D11Texture>(pBackBuffer);
            FrameBufferDescriptor desc;
            desc.colorFormat = DataFormat::RGBA32;
            desc.depthStencilFormat = DataFormat::D24U8;
            desc.width = width;
            desc.height = height;
            desc.usage = GraphicsResourceUsage::GPU_ReadWrite;
            this->back_buffer_ = std::make_shared<D3D11FrameBuffer>(backBufferTexture, desc);
            // this->Bind(frameBuffer);

            // Set the viewport
            D3D11_VIEWPORT viewport;
            ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

            viewport.TopLeftX = 0;
            viewport.TopLeftY = 0;
            viewport.Width = static_cast<FLOAT>(width);
            viewport.Height = static_cast<FLOAT>(height);
            viewport.MinDepth = 0;
            viewport.MaxDepth = 1;

            D3D11_RASTERIZER_DESC rasterizerStateDesc = {
        D3D11_FILL_SOLID,		// FillMode
        D3D11_CULL_NONE,
        FALSE,					// FrontCounterClockwise
        0,						// DepthBias
        0.0f,					// DepthBiasClamp
        0.0f,					// SlopeScaledDepthBias
        TRUE,					// DepthClipEnable
        FALSE,					// ScissorEnable
        FALSE,					// MultisampleEnable
        FALSE					// AntialiasedLineEnable
    };

    ID3D11RasterizerState * pRasterizerState = NULL;
    hr = this->d3d_device_->CreateRasterizerState( &rasterizerStateDesc, &pRasterizerState );
            CHECK_ASSERT(hr == S_OK);

    this->d3d_imm_context_->RSSetState( pRasterizerState );

            d3d_imm_context_->RSSetViewports(1, &viewport);

               D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc = {
                    TRUE,								// DepthEnable
                    D3D11_DEPTH_WRITE_MASK_ALL,			// DepthWriteMask
                    D3D11_COMPARISON_LESS,				// DepthFunc
                    FALSE,								// StencilEnable
                    D3D11_DEFAULT_STENCIL_READ_MASK,	// StencilReadMask
                    D3D11_DEFAULT_STENCIL_WRITE_MASK,	// StencilWriteMask
                    {
                        D3D11_STENCIL_OP_KEEP,			// FrontFace.StencilFailOp
                        D3D11_STENCIL_OP_KEEP,			// FrontFace.StencilDepthFailOp
                        D3D11_STENCIL_OP_KEEP,			// FrontFace.StencilPassOp
                        D3D11_COMPARISON_ALWAYS			// FrontFace.StencilFunc
                    },
                    {
                        D3D11_STENCIL_OP_KEEP,			// BackFace.StencilFailOp
                        D3D11_STENCIL_OP_KEEP,			// BackFace.StencilDepthFailOp
                        D3D11_STENCIL_OP_KEEP,			// BackFace.StencilPassOp
                        D3D11_COMPARISON_ALWAYS			// BackFace.StencilFunc
                    }
                };

                ID3D11DepthStencilState * pDepthStencilState = NULL;
                hr = this->d3d_device_->CreateDepthStencilState(&depthStencilStateDesc, &pDepthStencilState);
            CHECK_ASSERT(hr == S_OK);

                this->d3d_imm_context_->OMSetDepthStencilState(pDepthStencilState, 0);

                // this->InitPipeline();
        }
        void D3D11RenderEngine::Update()
        {
            const float bg[4] = {0.0f, 0.2f, 0.4f, 1.0f};
            auto color = std::dynamic_pointer_cast<D3D11Texture>(this->current_frame_buffer_->GetColor(0));
            // this->d3d_imm_context_->ClearRenderTargetView(color->AsRTV().Get(), bg);
            // this->TriangleDraw();
            // this->d3d_swap_chain_->Present(0, 0);
        }
        void D3D11RenderEngine::Deinit()
        {
            // this->DeinitPipeline();

            this->d3d_device_->Release();
            this->d3d_swap_chain_->Release();
            this->d3d_imm_context_->Release();
        }
        void D3D11RenderEngine::Render(const GraphicsBufferSharedPtr vertice, const GraphicsBufferSharedPtr indice)
        {
            if (vertice == nullptr || indice == nullptr) return;

            // const float bg[4] = {0.0f, 0.2f, 0.4f, 1.0f};
            // auto color = std::dynamic_pointer_cast<D3D11Texture>(this->current_frame_buffer_->GetColor(0));
            // this->d3d_imm_context_->ClearRenderTargetView(color->AsRTV().Get(), bg);
            // this->TriangleDraw();

            auto v = std::dynamic_pointer_cast<D3D11GraphicsBuffer>(vertice);
            auto i = std::dynamic_pointer_cast<D3D11GraphicsBuffer>(indice);

            UINT stride = v->descriptor_.resource.stride;
            UINT offset = 0;
            this->d3d_imm_context_->IASetVertexBuffers(0, 1, v->buffer_.GetAddressOf(), &stride, &offset);
            this->d3d_imm_context_->IASetIndexBuffer(i->buffer_.Get(), DXGI_FORMAT_R32_UINT, 0);

            // select which primtive type we are using
            this->d3d_imm_context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

            // draw the vertex buffer to the back buffer
            this->d3d_imm_context_->DrawIndexed((UINT)(i->descriptor_.resource.count), 0, 0);
        }
        void D3D11RenderEngine::PrintInfo()
        {
            std::cout << "D3D11" << std::endl;
        }

        static const std::string shader =
            "struct vs_in {\
                float3 position : POSITION;\
                float3 normal : NORMAL;\
                float2 texcoord : TEXCOORD;\
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
                // static constexpr size_t byte_size()
                // {
                //     return float3::byte_size + float4::byte_size;
                // }
                float3 pos;     // position
                float3 normal;  // normal
                float2 uv;      // uv
                float4 color;
                // float3 pos;
                // // float x, y, z;
                // float4 color;
        };
        void D3D11RenderEngine::InitPipeline()
        {
            auto hr = D3DCompile(shader.c_str(), shader.length(), nullptr, nullptr, nullptr, "vs_main", "vs_5_0", 0, 0, &vs_blob, nullptr);
            CHECK_ASSERT(hr == S_OK);
            hr = D3DCompile(shader.c_str(), shader.length(), nullptr, nullptr, nullptr, "ps_main", "ps_5_0", 0, 0, &ps_blob, nullptr);
            CHECK_ASSERT(hr == S_OK);

            hr = this->d3d_device_->CreateVertexShader(this->vs_blob->GetBufferPointer(), this->vs_blob->GetBufferSize(), nullptr, &this->vs);
            CHECK_ASSERT(hr == S_OK);
            hr = this->d3d_device_->CreatePixelShader(this->ps_blob->GetBufferPointer(), this->ps_blob->GetBufferSize(), nullptr, &this->ps);
            CHECK_ASSERT(hr == S_OK);

            // this->d3d_imm_context_->VSSetShader(this->vs, 0, 0);
            // this->d3d_imm_context_->PSSetShader(this->ps, 0, 0);

            D3D11_INPUT_ELEMENT_DESC input_desc[] = {
                {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
                {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
                {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
                {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
            };

            hr = this->d3d_device_->CreateInputLayout(input_desc, 4, this->vs_blob->GetBufferPointer(), this->vs_blob->GetBufferSize(), &this->layout);
            CHECK_ASSERT(hr == S_OK);

            // this->d3d_imm_context_->IASetInputLayout(this->layout);

            // create a triangle using the VERTEX struct
            VERTEX OurVertices[] = {
                {{0.0f, 0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
                {{0.45f, -0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
                {{-0.45f, -0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}}
                // {{0.0f, 0.5f, 0.0f},  {1.0f, 0.0f, 0.0f, 1.0f}},
                // {{0.45f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
                // {{-0.45f, -0.5f, 0.0f},  {0.0f, 0.0f, 1.0f, 1.0f}}
                // {0.0f, 0.5f, 0.0f,  {1.0f, 0.0f, 0.0f, 1.0f}},
                // {0.45f, -0.5f, 0.0f, {0.0f, 1.0f, 0.0f, 1.0f}},
                // {-0.45f, -0.5f, 0.0f,  {0.0f, 0.0f, 1.0f, 1.0f}}
            };

            // auto vsize = VERTEX::byte_size();
            // auto vsize = sizeof(VERTEX);
            auto varr_size = sizeof(OurVertices);

            // PRINT(sizeof(VERTEX));
            // PRINT(sizeof(OurVertices));
            // PRINT(float3::byte_size);
            // PRINT(sizeof(float3));
            // PRINT(sizeof(Test<float, 3>));
            // PRINT(vsize);
            // PRINT(varr_size);
            //, {0.45f, -0.5, 0.0f, {0.0f, 1.0f, 0.0f, 1.0f}},
            //     {
            //         -0.45f, -0.5f, 0.0f,
            //         {
            //             0.0f, 0.0f, 1.0f, 1.0f
            //         }
            //     }
            // };

            // create the vertex buffer
            D3D11_BUFFER_DESC bd;
            ZeroMemory(&bd, sizeof(bd));

            bd.Usage = D3D11_USAGE_DYNAMIC;              // write access access by CPU and GPU
            bd.ByteWidth = (UINT)varr_size;              // size is the VERTEX struct * 3
            bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;     // use as a vertex buffer
            bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;  // allow CPU to write in buffer

            hr = this->d3d_device_->CreateBuffer(&bd, NULL, &this->vertex_buffer);  // create the buffer
            CHECK_ASSERT(hr == S_OK);

            // copy the vertices into the buffer
            D3D11_MAPPED_SUBRESOURCE ms;
            this->d3d_imm_context_->Map(this->vertex_buffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);  // map the buffer
            std::memcpy(ms.pData, OurVertices, varr_size);                                               // copy the data
            this->d3d_imm_context_->Unmap(this->vertex_buffer, NULL);                                    // unmap the buffer
        }
        void D3D11RenderEngine::TriangleDraw()
        {
            // select which vertex buffer to display
            UINT stride = sizeof(VERTEX);
            UINT offset = 0;
            this->d3d_imm_context_->IASetVertexBuffers(0, 1, &this->vertex_buffer, &stride, &offset);

            // select which primtive type we are using
            this->d3d_imm_context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

            // draw the vertex buffer to the back buffer
            this->d3d_imm_context_->Draw(3, 0);
        }
        void D3D11RenderEngine::DeinitPipeline()
        {
            this->vs_blob->Release();
            this->ps_blob->Release();
            this->vs->Release();
            this->ps->Release();
            this->layout->Release();
            this->vertex_buffer->Release();
        }
        void D3D11RenderEngine::OnBind(const FrameBufferSharedPtr frameBuffer)
        {
            auto color = std::dynamic_pointer_cast<D3D11Texture>(frameBuffer->GetColor(0));
            auto depth = std::dynamic_pointer_cast<D3D11Texture>(frameBuffer->GetDepthStencil());
            this->d3d_imm_context_->OMSetRenderTargets(1, color->AsRTV().GetAddressOf(), depth == nullptr ? nullptr : depth->AsDSV().Get());
            // this->d3d_imm_context_->OMSetRenderTargets(1, color->AsRTV().GetAddressOf(), nullptr);
        }
        void D3D11RenderEngine::OnBind(const PipelineStateSharedPtr pipeline_state)
        {
            auto d3d_state = std::dynamic_pointer_cast<D3D11PipelineState>(pipeline_state);

            this->d3d_imm_context_->VSSetShader(d3d_state->vs_.Get(), 0, 0);
            this->d3d_imm_context_->PSSetShader(d3d_state->ps_.Get(), 0, 0);

            D3D11_INPUT_ELEMENT_DESC input_desc[] = {
                {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
                {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
                {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
                {"COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
                {"BLENDINDICES", 0, DXGI_FORMAT_R32G32B32A32_SINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
                {"BLENDWEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
            };

            auto hr = this->d3d_device_->CreateInputLayout(input_desc, (UINT)array_length(input_desc), d3d_state->vs_blob_->GetBufferPointer(), d3d_state->vs_blob_->GetBufferSize(), &this->layout);
            CHECK_ASSERT(hr == S_OK);

            this->d3d_imm_context_->IASetInputLayout(this->layout);
        }
        void D3D11RenderEngine::OnBind(const GraphicsBufferSharedPtr graphics_buffer)
        {
            auto d3d_gb = std::dynamic_pointer_cast<D3D11GraphicsBuffer>(graphics_buffer);
            auto desc = d3d_gb->descriptor_;
            this->d3d_imm_context_->VSSetConstantBuffers(static_cast<uint32_t>(desc.slot), 1, d3d_gb->buffer_.GetAddressOf());
        }
        void D3D11RenderEngine::OnBind(const TextureSharedPtr texture)
        {
            auto d3d_tex = std::dynamic_pointer_cast<D3D11Texture>(texture);
            auto desc = d3d_tex->descriptor_;
            this->d3d_imm_context_->PSSetShaderResources(static_cast<uint32_t>(desc.slot), 1, d3d_tex->AsSRV().GetAddressOf());
        }
        void D3D11RenderEngine::Clear(const FrameBufferSharedPtr frame_buffer, const color color /*= float4(0.0f, 0.2f, 0.4f, 1.0f)*/)
        {
            // const float bg[4] = {0.0f, 0.2f, 0.4f, 1.0f};
            auto color_buffer = std::dynamic_pointer_cast<D3D11Texture>(this->current_frame_buffer_->GetColor(0));
            auto depth_buffer = std::dynamic_pointer_cast<D3D11Texture>(this->current_frame_buffer_->GetDepthStencil());
            this->d3d_imm_context_->ClearRenderTargetView(color_buffer->AsRTV().Get(), color.data());
            this->d3d_imm_context_->ClearDepthStencilView(depth_buffer->AsDSV().Get(), D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1, 0);
        }

        void D3D11RenderEngine::OnEndFrame()
        {
            this->d3d_swap_chain_->Present(0, 0);
        }

        PipelineStateSharedPtr D3D11RenderEngine::OnRegister(const PipelineStateDescriptor& pipeline_desc)
        {
            return std::make_shared<D3D11PipelineState>(pipeline_desc);
        }
        TextureSharedPtr D3D11RenderEngine::Create(const TextureDescriptor& desc)
        {
            return std::make_shared<D3D11Texture>(desc);
        }
        FrameBufferSharedPtr D3D11RenderEngine::Create(const FrameBufferDescriptor& desc)
        {
            PRINT("Create D3D11FrameBuffer");
            return std::make_shared<D3D11FrameBuffer>(desc);
        }
        GraphicsBufferSharedPtr D3D11RenderEngine::Create(const GraphicsBufferDescriptor& desc)
        {
            PRINT("Create D3D11GraphicsBuffer");
            return std::make_shared<D3D11GraphicsBuffer>(desc);
        }

    }  // namespace Rendering
}  // namespace vEngine

extern "C"
{
    void CreateRenderEngine(std::unique_ptr<vEngine::Rendering::RenderEngine>& ptr)
    {
        ptr = std::make_unique<vEngine::Rendering::D3D11RenderEngine>();
    }
    void DestoryRenderEngine(std::unique_ptr<vEngine::Rendering::RenderEngine>& ptr)
    {
        ptr.reset();
    }
}