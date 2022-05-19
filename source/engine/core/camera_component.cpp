/// \file camera_component.cpp
/// \brief source file for Camera Component
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <cstring>
#include <vengine/core/camera_component.hpp>
#include <vengine/core/context.hpp>
#include <vengine/core/transform_component.hpp>
#include <vengine/core/transform_node.hpp>
#include <vengine/rendering/graphics_buffer.hpp>
#include <vengine/rendering/render_engine.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {

        /// constructor detailed defintion,
        /// should be 2 lines
        CameraComponent::CameraComponent()
        {
            auto cbuffer_desc = GraphicsBufferDescriptor();
            cbuffer_desc.type = GraphicsBufferType::GBT_CBuffer;
            cbuffer_desc.usage = GraphicsBufferUsage::GPU_CPU_Write_GPU_Read;
            cbuffer_desc.offset = 0;
            cbuffer_desc.stride = sizeof(vEngineCameraConstantBuffer);
            cbuffer_desc.count = 1;
            cbuffer_desc.total_size = cbuffer_desc.count * cbuffer_desc.stride;
            cbuffer_desc.slot = static_cast<GraphicsBufferSlot>(vEngineConstantBufferPerCamera);

            vEngineCameraConstantBuffer cb;
            cbuffer_desc.data = &cb;

            this->camera_constant_buffer_ = Context::GetInstance().GetRenderEngine().Create(cbuffer_desc);
        }
        void CameraComponent::OnBeginCamera()
        {
            auto cam = this->game_object_;
            vEngineCameraConstantBuffer cb;
            cb.camera_pos = float4(0, 0, 100, 1);

            auto trans = std::dynamic_pointer_cast<TransformNode>(this->Owner());
            cb.view_matrix = trans->transform_->game_object_->LocalToWorldTransform();
            // Math::Translate(cb.view_matrix, 0, 0, 100);
            // cb.view_matrix = Math::Transpose(cb.view_matrix);
            cb.proj_matrix = cam->ProjectionMatrix();
            // cb.proj_matrix = Math::Transpose(cb.proj_matrix);
            auto data = this->camera_constant_buffer_->Map();
            std::memcpy(data.data, &cb, sizeof(vEngineCameraConstantBuffer));
            // std::copy(&cb, &cb + sizeof(vEngineCameraConstantBuffer), data.data);
            this->camera_constant_buffer_->Unmap();

            Context::GetInstance().GetRenderEngine().OnBind(this->camera_constant_buffer_);
        }
    }  // namespace Core

}  // namespace vEngine