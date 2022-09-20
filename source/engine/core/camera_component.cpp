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
#include <vengine/rendering/graphics_buffer.hpp>
#include <vengine/rendering/render_engine.hpp>
#include <vengine/rendering/shared/data_cbuffer.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {
        using namespace Rendering;

        /// constructor detailed defintion,
        /// should be 2 lines
        CameraComponent::CameraComponent(const GameObjectType type) : Component(type)
        {
            GraphicsBufferDescriptor cbuffer_desc;
            cbuffer_desc.type = GraphicsResourceType::CBuffer;
            cbuffer_desc.usage = GraphicsResourceUsage::CPU_Write_GPU_Read;
            cbuffer_desc.resource.offset = 0;
            cbuffer_desc.resource.stride = sizeof(vEngineCameraConstantBuffer);
            cbuffer_desc.resource.count = 1;
            cbuffer_desc.resource.total_size = cbuffer_desc.resource.count * cbuffer_desc.resource.stride;
            cbuffer_desc.slot = static_cast<GraphicsBufferSlot>(vEngineConstantBufferPerCamera);

            vEngineCameraConstantBuffer cb;
            cbuffer_desc.resource.data = &cb;

            this->camera_constant_buffer_ = Context::GetInstance().GetRenderEngine()->Create(cbuffer_desc);
        }
        void CameraComponent::OnBeginCamera()
        {
            auto cam = this->GO();
            vEngineCameraConstantBuffer cb;
            cb.camera_pos = float4(0, 0, 100, 1);

            auto trans = this->Owner()->FirstOf<TransformComponent>();
            //TODO use rot to rotate forward/up vector
            auto rot = trans->GO()->Rotation();
            auto eye= trans->GO()->Translate();
            auto at = Math::TransformPoint(float4(0,0,1,1), Math::ToMatrix(rot));
            auto up = float3(0,1,0);
            cb.view_matrix = Math::LookAtLH(eye, float3(at.x(), at.y(), at.z()), up);
            // Math::Translate(cb.view_matrix, 0, 0, 100);
            // cb.view_matrix = Math::Transpose(cb.view_matrix);
            cb.proj_matrix = cam->ProjectionMatrix();
            // cb.proj_matrix = Math::Transpose(cb.proj_matrix);
            auto data = this->camera_constant_buffer_->Map();
            std::memcpy(data.data, &cb, sizeof(vEngineCameraConstantBuffer));
            // std::copy(&cb, &cb + sizeof(vEngineCameraConstantBuffer), data.data);
            this->camera_constant_buffer_->Unmap();

            Context::GetInstance().GetRenderEngine()->OnBind(this->camera_constant_buffer_);
        }
    }  // namespace Core

}  // namespace vEngine