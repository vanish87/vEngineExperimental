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
#include <vengine/rendering/shared/data_cbuffer.hpp>
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

            GraphicsBufferDescriptor cbuffer_desc;
            cbuffer_desc.type = GraphicsResourceType::CBuffer;
            cbuffer_desc.usage = GraphicsResourceUsage::CPU_Write_GPU_Read;
            cbuffer_desc.resource.offset = 0;
            cbuffer_desc.resource.stride = sizeof(vEngineCameraConstantBuffer);
            cbuffer_desc.resource.count = 1;
            cbuffer_desc.resource.total_size = cbuffer_desc.resource.count * cbuffer_desc.resource.stride;

            vEngineCameraConstantBuffer cb;
            cbuffer_desc.resource.data = &cb;

            // this->frame_constat_buffer_ = Context::GetInstance().GetRenderEngine().Create(cbuffer_desc);
        }
        FrameBuffer::~FrameBuffer() {}
        // void FrameBuffer::UpdateGPU(const float4x4 view_matrix, const float4x4 proj_matrix)
        // {
        //     UNUSED_PARAMETER(view_matrix);
        //     UNUSED_PARAMETER(proj_matrix);

        //     vEngineCameraConstantBuffer cb;
        //     cb.view_matrix = view_matrix;
        //     cb.proj_matrix = proj_matrix;
        //     auto data = this->frame_constat_buffer_->Map();
        //     memcpy(data.data, &cb, sizeof(vEngineCameraConstantBuffer));
        //     this->frame_constat_buffer_->Unmap();
        // }

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