/// \file d3d11_pipeline_state.cpp
/// \brief source file for D3D11 Pipeline State
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <d3dcompiler.h>

#include <vengine/core/context.hpp>
#include <vengine/rendering/d3d11_pipeline_state.hpp>
#include <vengine/rendering/d3d11_render_engine.hpp>
#include <vengine/rendering/shader.hpp>
#include <vengine/rendering/d3d11_shader_include.hpp>
// #include <vengine/rendering/d3d11_texture.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Rendering
    {
        // using namespace vEngine::Core;

        /// constructor detailed defintion,
        /// should be 2 lines
        D3D11PipelineState::D3D11PipelineState(const PipelineStateDescriptor& desc) : PipelineState(desc) 
        {
            // PRINT("D3D11PipelineState");
        }
        D3D11PipelineState::~D3D11PipelineState()
        {
            // PRINT("D3D11PipelineState Destructor");
        }

        void D3D11PipelineState::PrepareData()
        {
            if (this->vs_ == nullptr)
            {
                auto& re = Core::Context::GetInstance().GetRenderEngine();
                auto d3d_re = dynamic_cast<D3D11RenderEngine*>(re.get());
                auto device = d3d_re->Device();

                ComPtr<ID3DBlob> error;
                ComPtr<ID3DBlob> blob;
                D3D11ShaderInclude my_include;

                std::array<D3D_SHADER_MACRO, 1> macros = {{
                    {nullptr, nullptr},
                }};

                for (const auto& s : this->shaders_)
                {
                    // auto path = s.second->path.string();

                    auto target = D3D11RenderEngine::ShaderTypeToTarget(s.first);

                    PRINT(s.second->source);

                    // auto source_name = std::string("resource/shader/ps/ps.json");
                    auto source_name = target;
                    auto hr = D3DCompile(s.second->source.data(), s.second->source.size(), source_name.c_str(),
                                            macros.data(), &my_include, 
                                            "main", target.c_str(), 0, 0, blob.GetAddressOf(),
                                            error.GetAddressOf());
                    if (error != nullptr)
                    {
                        std::string err(static_cast<char*>(error->GetBufferPointer()), error->GetBufferSize());
                        PRINT(err);
                    }
                    CHECK_ASSERT(hr == S_OK);

                    switch (s.first)
                    {
                        case ShaderType::VertexShader:
                        {
                            hr = device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, this->vs_.GetAddressOf());
                            CHECK_ASSERT(hr == S_OK);

                            D3D11_INPUT_ELEMENT_DESC input_desc[] = {
                                {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
                                {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
                                {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
                                {"COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
                                {"BLENDINDICES", 0, DXGI_FORMAT_R32G32B32A32_SINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
                                {"BLENDWEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
                                {"BLENDINDICES", 1, DXGI_FORMAT_R32G32B32A32_SINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
                                {"BLENDWEIGHT", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
                            };
                            hr = device->CreateInputLayout(input_desc, (UINT)array_length(input_desc), blob->GetBufferPointer(), blob->GetBufferSize(), this->layout_.GetAddressOf());
                            CHECK_ASSERT(hr == S_OK);
                        }
                        break;
                        case ShaderType::PixelShader:
                        {
                            hr = device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, this->ps_.GetAddressOf());
                            CHECK_ASSERT(hr == S_OK);
                        }
                        default:
                            break;
                    }

                    blob.Reset();
                }

                D3D11_RASTERIZER_DESC rdesc = D3D11RenderEngine::ToD3D11RasterizerDesc(this->descriptor_.rasterizer_descriptor);
                auto hr = device->CreateRasterizerState(&rdesc, this->rasterizer_state_.GetAddressOf());
                CHECK_ASSERT(hr == S_OK);

                D3D11_DEPTH_STENCIL_DESC ddesc = D3D11RenderEngine::ToD3D11DepthStencilDesc(this->descriptor_.depth_stencil_descriptor);
                hr = device->CreateDepthStencilState(&ddesc, this->depth_stencil_state_.GetAddressOf());
                CHECK_ASSERT(hr == S_OK);
            }
        }
    }  // namespace Rendering
}  // namespace vEngine