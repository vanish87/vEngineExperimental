/// \file mesh.cpp
/// \brief source file for Mesh
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/mesh.hpp>
#include <vengine/core/context.hpp>
#include <vengine/rendering/render_engine.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {

        /// constructor detailed defintion,
        /// should be 2 lines
        Mesh::Mesh() : vertex_buffer_(nullptr), index_buffer_(nullptr) {}

        /// Load mesh from assimp lib
        /// store them in cpu side, then update to gpu later
        void Mesh::Load(const std::string filename)
        {
        }

        /// Create GPU related buffer
        /// ie. Index/Vertice buffer for rendering
        void Mesh::UpdateGPUBuffer()
        {
            GraphicsBufferDescriptor desc;
            desc.type = GraphicsBufferType::GBT_Vertex;
            desc.usage = GraphicsBufferUsage::GBU_GPU;
            this->vertex_buffer_ = Context::GetInstance().GetRenderEngine().Create(desc);

            desc.type = GraphicsBufferType::GBT_Index;
            desc.usage = GraphicsBufferUsage::GBU_GPU;
            this->index_buffer_ = Context::GetInstance().GetRenderEngine().Create(desc);
        }
    }  // namespace Core

}  // namespace vEngine