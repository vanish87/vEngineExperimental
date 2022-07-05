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
            auto re = &Core::Context::GetInstance().GetRenderEngine();
            auto d3d_re = dynamic_cast<D3D11RenderEngine*>(re);
            auto device = d3d_re->Device();

            ComPtr<ID3DBlob> error;
            ComPtr<ID3DBlob> blob;
            auto target = "vs_5_0";

            for(const auto& s : this->shaders_)
            {
                switch (s.first)
                {
                    case ShaderType::VS:
                    {
                        target = "vs_5_0";
                    }
                    break;
                    case ShaderType::PS:
                    {
                        target = "ps_5_0";
                    }

                    default:
                        break;
                }
                auto path = s.second->path.string();
                auto hr = D3DCompile(s.second->content.data(), s.second->content.size(), path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", target, 0, 0, blob.GetAddressOf(),
                                     error.GetAddressOf());
                if (error != nullptr)
                {
                    std::string err(static_cast<char*>(error->GetBufferPointer()), error->GetBufferSize());
                    PRINT(err);
                }
                CHECK_ASSERT(hr == S_OK);

                switch (s.first)
                {
                    case ShaderType::VS:
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
                    case ShaderType::PS:
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
    }  // namespace Rendering
}  // namespace vEngine