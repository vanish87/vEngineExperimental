/// \file d3d11_pipeline_state.hpp
/// \brief Head file for D3D11 Pipeline State
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_RENDERING_D3D11_PIPELINE_STATE_HPP
#define _VENGINE_RENDERING_D3D11_PIPELINE_STATE_HPP

#pragma once

#include <vengine/rendering/d3d11_predeclear.hpp>
#include <vengine/rendering/pipeline_state.hpp>

namespace vEngine
{
    namespace Rendering
    {
        /// \brief Unity-like Graphics buffer
        ///
        /// Graphics buffer could be index/vertex buffer or
        /// constant buffer.
        /// It could be used in cpu and/or gpu
        // template<typename T>
        class D3D11PipelineState : public PipelineState
        {
            public:
                /// \brief brief constructor description.
                D3D11PipelineState(const PipelineStateDescriptor& desc);

                void PrepareData() override;

                ComPtr<ID3D11VertexShader> vs_;
                ComPtr<ID3D11PixelShader> ps_;
                ComPtr<ID3D11InputLayout> layout_;

                ComPtr<ID3D11RasterizerState> rasterizer_state_;
                ComPtr<ID3D11DepthStencilState> depth_stencil_state_;
        };
    }  // namespace Rendering
}  // namespace vEngine

#endif /* _VENGINE_RENDERING_D3D11_PIPELINE_STATE_HPP */
