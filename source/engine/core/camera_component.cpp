/// \file camera_component.cpp
/// \brief source file for Camera Component
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/camera_component.hpp>

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
    }  // namespace Core

}  // namespace vEngine