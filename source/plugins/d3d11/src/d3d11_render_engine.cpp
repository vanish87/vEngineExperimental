
#include <d3dcompiler.h>
#include <dxcapi.h>

#include <cstring>
#include <filesystem>
#include <shlobj.h>

#include <vengine/rendering/d3d11_render_engine.hpp>
#include <D3D11_RENDERING_PLUGIN_API.hpp>

#include <vengine/core/context.hpp>
#include <vengine/core/window.hpp>
#include <vengine/core/vector.hpp>
#include <vengine/core/math.hpp>
#include <vengine/core/game_object_factory.hpp>
#include <vengine/rendering/d3d11_frame_buffer.hpp>
#include <vengine/rendering/d3d11_graphics_buffer.hpp>
#include <vengine/rendering/d3d11_pipeline_state.hpp>
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
        D3D11_RASTERIZER_DESC D3D11RenderEngine::ToD3D11RasterizerDesc(RasterizerDescriptor desc)
        {
            D3D11_RASTERIZER_DESC d3ddesc;
            switch (desc.fill_mode)
            {
                case FillMode::Solid:
                    d3ddesc.FillMode = D3D11_FILL_SOLID;
                    break;
                case FillMode::Wireframe:
                    d3ddesc.FillMode = D3D11_FILL_WIREFRAME;
                    break;
                default:
                    break;
            }
            switch (desc.cull_mode)
            {
                case CullMode::None:
                    d3ddesc.CullMode = D3D11_CULL_NONE;
                    break;
                case CullMode::Front:
                    d3ddesc.CullMode = D3D11_CULL_FRONT;
                    break;
                case CullMode::Back:
                    d3ddesc.CullMode = D3D11_CULL_BACK;
                    break;
                default:
                    break;
            }

            switch (desc.front_facing)
            {
                case FrontFacingDirection::Clockwise:
                    d3ddesc.FrontCounterClockwise = false;
                    break;
                case FrontFacingDirection::CounterClockwise:
                    d3ddesc.FrontCounterClockwise = true;
                    break;
                default:
                    break;
            }

            d3ddesc.DepthBias = desc.depth_bias;
            d3ddesc.DepthBiasClamp = desc.depth_bias_clamp;
            d3ddesc.SlopeScaledDepthBias = desc.slop_scaled_depth_bias;
            d3ddesc.DepthClipEnable = desc.depth_clip_enabled;
            d3ddesc.MultisampleEnable = desc.multisample_enabled;
            d3ddesc.AntialiasedLineEnable = desc.antialiased_line_enabled;
            d3ddesc.ScissorEnable = false;

            return d3ddesc;
        }
        D3D11_DEPTH_STENCIL_DESC D3D11RenderEngine::ToD3D11DepthStencilDesc(DepthStencilDescriptor desc)
        {
            D3D11_DEPTH_STENCIL_DESC d3ddesc;
            switch (desc.depth_write_mask)
            {
                case DepthWriteMask::All:
                    d3ddesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
                    break;
                case DepthWriteMask::Zero:
                    d3ddesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
                    break;
                default:
                    break;
            }
            switch (desc.comparison_func)
            {
                case ComparisonFunc::Never:
                    d3ddesc.DepthFunc = D3D11_COMPARISON_NEVER;
                    break;
                case ComparisonFunc::Less:
                    d3ddesc.DepthFunc = D3D11_COMPARISON_LESS;
                    break;
                case ComparisonFunc::Equal:
                    d3ddesc.DepthFunc = D3D11_COMPARISON_EQUAL;
                    break;
                case ComparisonFunc::LessEqual:
                    d3ddesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
                    break;
                case ComparisonFunc::Greater:
                    d3ddesc.DepthFunc = D3D11_COMPARISON_GREATER;
                    break;
                case ComparisonFunc::NotEqual:
                    d3ddesc.DepthFunc = D3D11_COMPARISON_NOT_EQUAL;
                    break;
                case ComparisonFunc::GreatEqual:
                    d3ddesc.DepthFunc = D3D11_COMPARISON_GREATER_EQUAL;
                    break;
                case ComparisonFunc::Always:
                    d3ddesc.DepthFunc = D3D11_COMPARISON_ALWAYS;
                    break;
                default:
                    break;
            }

            d3ddesc.DepthEnable = desc.depth_enabled;
            d3ddesc.StencilEnable = desc.stencil_enabled;
            d3ddesc.StencilReadMask = desc.stencil_read_mask;
            d3ddesc.StencilWriteMask = desc.stencil_write_mask;
            return d3ddesc;
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
        std::string D3D11RenderEngine::ShaderTypeToTarget(const ShaderType type)
        {
            std::string version = "5_0";
            switch (type)
            {
                case ShaderType::VertexShader: return "vs_" + version;
                case ShaderType::HullShader: return "hs_" + version;
                case ShaderType::TessellatorShader: return "ts_" + version;
                case ShaderType::DomainShader: return "ds_" + version;
                case ShaderType::GeometryShader: return "gs_" + version;
                case ShaderType::PixelShader: return "ps_" + version;
                case ShaderType::ComputeShader: return "cs_" + version;
                default:
                    break;
            }

            return "";
        }

        void D3D11RenderEngine::InitDebug()
        {
            LPWSTR programFilesPath = nullptr;
            SHGetKnownFolderPath(FOLDERID_ProgramFiles, KF_FLAG_DEFAULT, NULL, &programFilesPath);

            std::filesystem::path pixInstallationPath = programFilesPath;
            pixInstallationPath /= "Microsoft PIX";

            std::wstring newestVersionFound;

            for (auto const& directory_entry : std::filesystem::directory_iterator(pixInstallationPath))
            {
                if (directory_entry.is_directory())
                {
                    if (newestVersionFound.empty() || newestVersionFound < directory_entry.path().filename().c_str())
                    {
                        newestVersionFound = directory_entry.path().filename().c_str();
                    }
                }
            }

            if (newestVersionFound.empty())
            {
                // TODO: Error, no PIX installation found
            }

            auto pix_path = pixInstallationPath / newestVersionFound / "WinPixGpuCapturer.dll";
            if (::GetModuleHandle("WinPixGpuCapturer.dll") == 0)
            {
                ::LoadLibrary(pix_path.string().c_str());
            }
        }
        void D3D11RenderEngine::Init()
        {
            // this->InitDebug();

            // TODO Use IDXGIFactory to check adapters

            const auto config = Context::GetInstance().CurrentConfigure();

            D3D_FEATURE_LEVEL feature_level;
            auto hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, this->d3d_device_.GetAddressOf(), &feature_level,
                                        this->d3d_imm_context_.GetAddressOf());
            CHECK_ASSERT(hr == S_OK);
            CHECK_ASSERT_NOT_NULL(this->d3d_device_);
            CHECK_ASSERT_NOT_NULL(this->d3d_imm_context_);

            if (config.graphics_configure.output == Output::Window)
            {
                auto window = Context::GetInstance().CurrentWindow();
                auto hwnd = static_cast<HWND>(window->WindowHandle());
                auto width = config.graphics_configure.width;
                auto height = config.graphics_configure.height;

// DXGI_SWAP_CHAIN_DESC scd;
// // clear out the struct for use
// ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

// // fill the swap chain description struct
// scd.BufferCount = 1;  // one back buffer
// scd.BufferDesc.Width = width;
// scd.BufferDesc.Height = height;
// scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // use 32-bit color
// scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;   // how swap chain is to be used
// scd.OutputWindow = hwnd;                             // the window to be used
// scd.SampleDesc.Count = 1;                            // how many multisamples
// scd.Windowed = true;                                 // windowed/full-screen mode
// #pragma clang diagnostic ignored "-Wlanguage-extension-token"
                ComPtr<IDXGIDevice2> pDXGIDevice;
                hr = this->d3d_device_->QueryInterface(__uuidof(IDXGIDevice2), (void**)pDXGIDevice.GetAddressOf());
                CHECK_ASSERT(hr == S_OK);

                ComPtr<IDXGIAdapter> pDXGIAdapter;
                hr = pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pDXGIAdapter.GetAddressOf());
                CHECK_ASSERT(hr == S_OK);

                ComPtr<IDXGIFactory2> pIDXGIFactory;
                hr = pDXGIAdapter->GetParent(__uuidof(IDXGIFactory2), (void**)pIDXGIFactory.GetAddressOf());
                CHECK_ASSERT(hr == S_OK);
// #pragma clang diagnostic warning "-Wlanguage-extension-token"

                // hr = pIDXGIFactory->CreateSwapChainForHwnd(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &scd, &d3d_swap_chain_, &d3d_device_, nullptr,
                // &d3d_imm_context_);

                DXGI_SWAP_CHAIN_DESC1 scd1;
                // clear out the struct for use
                ZeroMemory(&scd1, sizeof(DXGI_SWAP_CHAIN_DESC1));
                scd1.Width = width;
                scd1.Height = height;
                scd1.Format = DXGI_FORMAT_R8G8B8A8_UNORM;            // use 32-bit color
                scd1.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;  // how swap chain is to be used
                scd1.BufferCount = 2;
                scd1.SampleDesc.Count = 1;
                hr = pIDXGIFactory->CreateSwapChainForHwnd(this->d3d_device_.Get(), hwnd, &scd1, nullptr, nullptr, this->d3d_swap_chain_.GetAddressOf());

                CHECK_ASSERT(hr == S_OK);
                CHECK_ASSERT_NOT_NULL(this->d3d_swap_chain_);

// #pragma clang diagnostic ignored "-Wlanguage-extension-token"
                // get the address of the back buffer
                ID3D11Texture2D* pBackBuffer;
                hr = this->d3d_swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
// #pragma clang diagnostic warning "-Wlanguage-extension-token"
                CHECK_ASSERT(hr == S_OK);
                auto backBufferTexture = std::make_shared<D3D11Texture>(pBackBuffer);

                FrameBufferDescriptor desc;
                desc.colorFormat = DataFormat::RGBA32;
                desc.depthStencilFormat = DataFormat::D24U8;
                desc.width = width;
                desc.height = height;
                desc.usage = GraphicsResourceUsage::GPU_ReadWrite;
                this->back_buffer_ = std::make_shared<D3D11FrameBuffer>(desc);

                TextureDescriptor tdesc;
                tdesc.width = desc.width;
                tdesc.height = desc.height;
                tdesc.depth = 1;
                tdesc.format = desc.depthStencilFormat;
                tdesc.dimension = TextureDimension::TD_2D;
                tdesc.type = GraphicsResourceType::Depth;
                tdesc.usage = GraphicsResourceUsage::GPU_ReadWrite;
                tdesc.resource.data = nullptr;
                auto depth_tex = GameObjectFactory::Create<GameObjectType::Texture, Texture>(tdesc);

                this->back_buffer_->BindColor(backBufferTexture, 0);
                this->back_buffer_->BindDepthStencil(depth_tex);

                // Note: before render camera scene.cpp will bind camera's frame buffer
                //  this->Bind(this->back_buffer_);

                // Set the viewport
                D3D11_VIEWPORT viewport;
                ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

                viewport.TopLeftX = 0;
                viewport.TopLeftY = 0;
                viewport.Width = static_cast<FLOAT>(width);
                viewport.Height = static_cast<FLOAT>(height);
                viewport.MinDepth = 0;
                viewport.MaxDepth = 1;
                d3d_imm_context_->RSSetViewports(1, &viewport);
            }

            // this->InitPipeline();
        }
        void D3D11RenderEngine::Update()
        {
            // const float bg[4] = {0.0f, 0.2f, 0.4f, 1.0f};
            // auto color = std::dynamic_pointer_cast<D3D11Texture>(this->current_frame_buffer_->GetColor(0));
            // this->d3d_imm_context_->ClearRenderTargetView(color->AsRTV().Get(), bg);
            // this->TriangleDraw();
            // this->d3d_swap_chain_->Present(0, 0);
        }
        void D3D11RenderEngine::Deinit()
        {
            // this->DeinitPipeline();

            this->d3d_device_.Reset();
            this->d3d_imm_context_.Reset();

            if (this->d3d_swap_chain_ != nullptr) this->d3d_swap_chain_.Reset();
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

            UINT stride = v->buffer_descriptor_.resource.stride;
            UINT offset = 0;
            this->d3d_imm_context_->IASetVertexBuffers(0, 1, v->buffer_.GetAddressOf(), &stride, &offset);
            this->d3d_imm_context_->IASetIndexBuffer(i->buffer_.Get(), DXGI_FORMAT_R32_UINT, 0);

            // select which primtive type we are using
            this->d3d_imm_context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

            // draw the vertex buffer to the back buffer
            this->d3d_imm_context_->DrawIndexed((UINT)(i->buffer_descriptor_.resource.count), 0, 0);
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
            this->d3d_imm_context_->IASetInputLayout(d3d_state->layout_.Get());

            this->d3d_imm_context_->RSSetState(d3d_state->rasterizer_state_.Get());
            this->d3d_imm_context_->OMSetDepthStencilState(d3d_state->depth_stencil_state_.Get(), 0);
        }
        void D3D11RenderEngine::OnBind(const GraphicsBufferSharedPtr graphics_buffer)
        {
            auto d3d_gb = std::dynamic_pointer_cast<D3D11GraphicsBuffer>(graphics_buffer);
            auto desc = d3d_gb->buffer_descriptor_;
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
            UNUSED_PARAMETER(frame_buffer);
            // const float bg[4] = {0.0f, 0.2f, 0.4f, 1.0f};
            auto color_buffer = std::dynamic_pointer_cast<D3D11Texture>(this->current_frame_buffer_->GetColor(0));
            auto depth_buffer = std::dynamic_pointer_cast<D3D11Texture>(this->current_frame_buffer_->GetDepthStencil());
            this->d3d_imm_context_->ClearRenderTargetView(color_buffer->AsRTV().Get(), Math::ToFloat(color).data());
            this->d3d_imm_context_->ClearDepthStencilView(depth_buffer->AsDSV().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
        }

        void D3D11RenderEngine::OnEndFrame()
        {
            this->d3d_swap_chain_->Present(0, 0);
        }

        // PipelineStateSharedPtr D3D11RenderEngine::Create(const PipelineStateDescriptor& pipeline_desc)
        // {
        //     return GameObjectFactory::Create<D3D11PipelineState>(pipeline_desc);
        // }
        // TextureSharedPtr D3D11RenderEngine::Create(const TextureDescriptor& desc)
        // {
        //     return GameObjectFactory::Create<D3D11Texture>(desc);
        // }
        // FrameBufferSharedPtr D3D11RenderEngine::Create(const FrameBufferDescriptor& desc)
        // {
        //     PRINT("Create D3D11FrameBuffer");
        //     return GameObjectFactory::Create<D3D11FrameBuffer>(desc);
        // }
        // GraphicsBufferSharedPtr D3D11RenderEngine::Create(const GraphicsBufferDescriptor& desc)
        // {
        //     PRINT("Create D3D11GraphicsBuffer");
        //     return GameObjectFactory::Create<D3D11GraphicsBuffer>(desc);
        // }

    }  // namespace Rendering
}  // namespace vEngine

extern "C"
{
    D3D11_RENDERING_PLUGIN_API void CreateRenderEngine(std::unique_ptr<vEngine::Rendering::RenderEngine>& ptr)
    {
        ptr = std::make_unique<vEngine::Rendering::D3D11RenderEngine>();
    }
    D3D11_RENDERING_PLUGIN_API void DestoryRenderEngine(std::unique_ptr<vEngine::Rendering::RenderEngine>& ptr)
    {
        ptr.reset();
    }
}