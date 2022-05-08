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
            cbuffer_desc.type = GraphicsBufferType::GBT_CBuffer;
            cbuffer_desc.usage = GraphicsBufferUsage::GPU_CPU_Write_GPU_Read;
            cbuffer_desc.offset = 0;
            cbuffer_desc.stride = sizeof(vEngineObjectConstantBuffer);
            cbuffer_desc.count = 1;
            cbuffer_desc.total_size = cbuffer_desc.count * cbuffer_desc.stride;

            vEngineObjectConstantBuffer cb;
            cbuffer_desc.data = &cb;

            this->mesh_constant_buffer_ = Context::GetInstance().GetRenderEngine().Create(cbuffer_desc);
        }

    }  // namespace Rendering

}  // namespace vEngine