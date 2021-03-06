/// \file material.cpp
/// \brief source file for Material
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/context.hpp>
#include <vengine/core/material.hpp>
#include <vengine/rendering/render_engine.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {

        /// constructor detailed defintion,
        /// should be 2 lines
        Material::Material(const std::string vs_name, const std::string ps_name) : vs_name_{vs_name}, ps_name_{ps_name} {}

        bool Material::Load()
        {
            // this->d3d_imm_context_->VSSetShader(this->vs, 0, 0);
            // this->d3d_imm_context_->PSSetShader(this->ps, 0, 0);

            // D3D11_INPUT_ELEMENT_DESC input_desc[] = {
            //     {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            //     {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
            // };

            // hr = this->d3d_device_->CreateInputLayout(input_desc, 2, this->vs_blob->GetBufferPointer(), this->vs_blob->GetBufferSize(), &this->layout);
            // CHECK_ASSERT(hr == S_OK);

            // this->d3d_imm_context_->IASetInputLayout(this->layout);

            // this->Load(this->vs_shader_);
            // this->Load(this->ps_shader_);

            PipelineStateDescriptor desc;
            desc.vs_name = this->vs_name_;
            desc.ps_name = this->ps_name_;
            this->pipeline_state_ = Context::GetInstance().GetRenderEngine().Register(desc);
            Context::GetInstance().GetRenderEngine().Bind(this->pipeline_state_);

            return true;
        }

    }  // namespace Core

}  // namespace vEngine