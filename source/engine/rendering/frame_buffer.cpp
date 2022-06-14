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

            TextureDescriptor tdesc;
            tdesc.width = desc.width;
            tdesc.height = desc.height;
            tdesc.depth = 1;
            tdesc.format = desc.depthStencilFormat;
            tdesc.dimension = TextureDimension::TD_2D;
            tdesc.type = GraphicsResourceType::Depth;
            tdesc.usage = GraphicsResourceUsage::GPU_ReadWrite;
            tdesc.resource.data = nullptr;

            this->depthStencilTexture_ = Context::GetInstance().GetRenderEngine().Create(tdesc);

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