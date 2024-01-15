/// \file camera_component.cpp
/// \brief source file for Camera Component
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/ui/ui_component.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace UI
    {
        using namespace Rendering;

        /// constructor detailed defintion,
        /// should be 2 lines
        UIComponent::UIComponent()
        {
            // GraphicsBufferDescriptor cbuffer_desc;
            // cbuffer_desc.type = GraphicsResourceType::CBuffer;
            // cbuffer_desc.usage = GraphicsResourceUsage::CPU_Write_GPU_Read;
            // cbuffer_desc.stride = sizeof(vEngineCameraConstantBuffer);
            // cbuffer_desc.count = 1;
            // cbuffer_desc.slot = static_cast<GraphicsBufferSlot>(vEngineConstantBufferPerCamera);

            // this->camera_constant_buffer_ = GameObjectFactory::Create<GameObjectType::GraphicsBuffer, GraphicsBuffer>(cbuffer_desc);
        }
        // void UIComponent::OnBeginCamera()
        // {
        //     auto cam = this->GO();
        //     vEngineCameraConstantBuffer cb;

        //     auto trans = this->Owner()->FirstOf<TransformComponent>();
        //     // TODO use rot to rotate forward/up vector
        //     auto rot = trans->GO()->Rotation();
        //     auto eye = trans->GO()->Translate();
        //     auto at = Math::TransformPoint(float4(0, 0, 1, 1), Math::ToMatrix(rot));
        //     auto up = float3(0, 1, 0);
        //     cb.view_matrix = Math::LookAtLH(eye, float3(at.x(), at.y(), at.z()), up);
        //     // Math::Translate(cb.view_matrix, 0, 0, 100);
        //     // cb.view_matrix = Math::Transpose(cb.view_matrix);
        //     cb.proj_matrix = cam->ProjectionMatrix();
        //     // cb.proj_matrix = Math::Transpose(cb.proj_matrix);
        //     auto data = this->camera_constant_buffer_->Map();
        //     memcpy(data.data, &cb, sizeof(vEngineCameraConstantBuffer));
        //     // std::copy(&cb, &cb + sizeof(vEngineCameraConstantBuffer), data.data);
        //     this->camera_constant_buffer_->Unmap();

        //     Context::GetInstance().GetRenderEngine()->OnBind(this->camera_constant_buffer_);
        // }
    }  // namespace Core

}  // namespace vEngine