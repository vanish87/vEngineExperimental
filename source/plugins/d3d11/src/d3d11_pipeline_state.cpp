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
            ComPtr<ID3DBlob> error;

            auto vs = this->vs_shader_;
            auto hr = D3DCompile(vs->content.data(), vs->content.size(), vs->name.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "vs_main", "vs_5_0", 0, 0, vs_blob_.GetAddressOf(), error.GetAddressOf());
            if (error != nullptr)
            {
                std::string err(static_cast<char*>(error->GetBufferPointer()), error->GetBufferSize());
                PRINT(err);
            }
            CHECK_ASSERT(hr == S_OK);

            auto ps = this->ps_shader_;
            hr = D3DCompile(ps->content.data(), ps->content.size(), ps->name.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "ps_main", "ps_5_0", 0, 0, ps_blob_.GetAddressOf(), error.GetAddressOf());
            if (error != nullptr)
            {
                std::string err(static_cast<char*>(error->GetBufferPointer()), error->GetBufferSize());
                PRINT(err);
            }
            CHECK_ASSERT(hr == S_OK);

            auto re = &Core::Context::GetInstance().GetRenderEngine();
            auto d3d_re = dynamic_cast<D3D11RenderEngine*>(re);
            auto device = d3d_re->Device();

            hr = device->CreateVertexShader(this->vs_blob_->GetBufferPointer(), this->vs_blob_->GetBufferSize(), nullptr, this->vs_.GetAddressOf());
            CHECK_ASSERT(hr == S_OK);

            hr = device->CreatePixelShader(this->ps_blob_->GetBufferPointer(), this->ps_blob_->GetBufferSize(), nullptr, this->ps_.GetAddressOf());
            CHECK_ASSERT(hr == S_OK);


            D3D11_RASTERIZER_DESC rdesc = D3D11RenderEngine::ToD3D11RasterizerDesc(this->descriptor_.rasterizer_descriptor);
            hr = device->CreateRasterizerState(&rdesc, this->rasterizer_state_.GetAddressOf());
            CHECK_ASSERT(hr == S_OK);

            D3D11_DEPTH_STENCIL_DESC ddesc = D3D11RenderEngine::ToD3D11DepthStencilDesc(this->descriptor_.depth_stencil_descriptor);
            hr = device->CreateDepthStencilState(&ddesc, this->depth_stencil_state_.GetAddressOf());
            CHECK_ASSERT(hr == S_OK);
        }
    }  // namespace Rendering
}  // namespace vEngine