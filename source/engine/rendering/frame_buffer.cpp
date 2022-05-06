/// \file frame_buffer.cpp
/// \brief source file for Frame Buffer
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/context.hpp>
#include <vengine/rendering/frame_buffer.hpp>
#include <vengine/rendering/graphics_buffer.hpp>
#include <vengine/rendering/render_engine.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Rendering
    {
        FrameBuffer::FrameBuffer(const FrameBufferDescriptor& desc)
        {
            UNUSED_PARAMETER(desc);
        }

        /// constructor detailed defintion,
        /// should be 2 lines
        FrameBuffer::FrameBuffer(TextureSharedPtr backBuffer, const FrameBufferDescriptor& desc)
        {
            UNUSED_PARAMETER(desc);
            // auto& re = Context::GetInstance().GetRenderEngine();
            this->colorTextures_.push_back(backBuffer);
            // this->depthStencilTexture_ =

            auto cbuffer_desc = GraphicsBufferDescriptor();
            cbuffer_desc.type = GraphicsBufferType::GBT_CBuffer;
            cbuffer_desc.usage = GraphicsBufferUsage::GPU_CPU_Write_GPU_Read;
            cbuffer_desc.offset = 0;
            cbuffer_desc.stride = sizeof(vEngineFrameConstantBuffer);
            cbuffer_desc.count = 1;
            cbuffer_desc.total_size = cbuffer_desc.count * cbuffer_desc.stride;

            vEngineFrameConstantBuffer cb;
            cbuffer_desc.data = &cb;

            this->frame_constat_buffer_ = Context::GetInstance().GetRenderEngine().Create(cbuffer_desc);
        }
        FrameBuffer::~FrameBuffer() {}
        void FrameBuffer::UpdateGPU(const float4x4 view_matrix, const float4x4 proj_matrix)
        {
            UNUSED_PARAMETER(view_matrix);
            UNUSED_PARAMETER(proj_matrix);

            vEngineFrameConstantBuffer cb;
            cb.view_matrix = view_matrix;
            cb.proj_matrix = proj_matrix;
            auto data = this->frame_constat_buffer_->Map();
            memcpy(data.data, &cb, sizeof(vEngineFrameConstantBuffer));
            this->frame_constat_buffer_->Unmap();
        }

        /// A detailed function description, it
        /// should be 2 lines at least.
        // int MyClass::GetVariable(int p1, float p2)
        // {
        //     UNUSED_PARAMETER(p1);
        //     UNUSED_PARAMETER(p2);
        //     return 1;
        // }
    }  // namespace Rendering
}  // namespace vEngine