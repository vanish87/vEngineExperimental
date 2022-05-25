/// \file mesh_renderer_component.cpp
/// \brief source file for Mesh Renderer Component
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/mesh_renderer_component.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Rendering
    {

        /// constructor detailed defintion,
        /// should be 2 lines
        MeshRendererComponent::MeshRendererComponent()
        {
            auto cbuffer_desc = GraphicsBufferDescriptor();
            cbuffer_desc.type = GraphicsResourceType::CBuffer;
            cbuffer_desc.usage = GraphicsResourceUsage::CPU_Write_GPU_Read;
            cbuffer_desc.resource.offset = 0;
            cbuffer_desc.resource.stride = sizeof(vEngineObjectConstantBuffer);
            cbuffer_desc.resource.count = 1;
            cbuffer_desc.resource.total_size = cbuffer_desc.resource.count * cbuffer_desc.resource.stride;
            cbuffer_desc.slot = static_cast<GraphicsBufferSlot>(vEngineConstantBufferPerObject);

            vEngineObjectConstantBuffer cb;
            cbuffer_desc.resource.data = &cb;

            this->mesh_constant_buffer_ = Context::GetInstance().GetRenderEngine().Create(cbuffer_desc);
        }

    }  // namespace Rendering

}  // namespace vEngine