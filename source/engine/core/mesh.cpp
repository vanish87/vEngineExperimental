/// \file mesh.cpp
/// \brief source file for Mesh
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <vengine/core/context.hpp>
#include <vengine/core/mesh.hpp>
#include <vengine/rendering/render_engine.hpp>


/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {

        /// constructor detailed defintion,
        /// should be 2 lines
        Mesh::Mesh() : vertex_buffer_(nullptr), index_buffer_(nullptr)
        {
            PRINT("mesh object created");
        }

        /// Load mesh from assimp lib
        /// store them in cpu side, then update to gpu later
        void Mesh::Load(const std::string file_name)
        {
            // PRINT("Load mesh from file " + file_name);
            this->file_name_ = file_name;
        }
        bool Mesh::Load()
        {
            this->file_name_ = "bunny.obj";
            PRINT("Load mesh from file " + this->file_name_);

            Assimp::Importer importer;

            const aiScene* pScene = importer.ReadFile(this->file_name_, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);

            UNUSED_PARAMETER(pScene);

            return true;
        }

        /// Create GPU related buffer
        /// ie. Index/Vertice buffer for rendering
        void Mesh::UpdateGPUBuffer()
        {
            if (this->vertex_buffer_ == nullptr)
            {
                PRINT("Create mesh vertex Buffer");
                GraphicsBufferDescriptor desc;
                desc.type = GraphicsBufferType::GBT_Vertex;
                desc.usage = GraphicsBufferUsage::GBU_GPU;
                this->vertex_buffer_ = Context::GetInstance().GetRenderEngine().Create(desc);
            }

            if (this->index_buffer_ == nullptr)
            {
                PRINT("Create mesh index Buffer");
                GraphicsBufferDescriptor desc;
                desc.type = GraphicsBufferType::GBT_Index;
                desc.usage = GraphicsBufferUsage::GBU_GPU;
                this->index_buffer_ = Context::GetInstance().GetRenderEngine().Create(desc);
            }
        }
    }  // namespace Core

}  // namespace vEngine