/// \file mesh.cpp
/// \brief source file for Mesh
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/context.hpp>
#include <vengine/core/mesh.hpp>
#include <vengine/core/resource_loader.hpp>
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
        Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
        {
            this->vertex_data_.clear();
            this->index_data_.clear();

            this->vertex_data_.insert(this->vertex_data_.end(), vertices.begin(), vertices.end());
            this->index_data_.insert(this->index_data_.end(), indices.begin(), indices.end());

            this->loaded = true;
        }

        Mesh::~Mesh()
        {
            this->vertex_data_.clear();
            this->index_data_.clear();
        }

        /// Load mesh from assimp lib
        /// store them in cpu side, then update to gpu later
        void Mesh::Load(const std::string file_name)
        {
            // PRINT("Load mesh from file " + file_name);
            this->file_name_ = file_name;
            PRINT_AND_BREAK("Not implemented");

            // ResourceLoader::GetInstance().LoadAsync(shared_from_this(),
            // [&](IResourceSharedPtr c)
            // {
            //     UNUSED_PARAMETER(c);
            //     PRINT(this->file_name_ << " Resource loaded");
            // });
        }
        ResourceState Mesh::CurrentState()
        {
            return ResourceState::Unknown;
        }
        bool Mesh::Load()
        {
            // this->file_name_ = "bunny.obj";
            // PRINT("Load mesh from file " + this->file_name_);

            Assimp::Importer importer;
            auto pScene = importer.ReadFile(this->file_name_, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
            this->HandleNode(pScene->mRootNode, pScene);

            // auto z = 20.0f;
            // Vertex v1;
            // v1.pos = float3(-0.5f, 0.7f, z);
            // Vertex v2;
            // v2.pos = float3(-0.5f, -0.5, z);
            // Vertex v3;
            // v3.pos = float3(0.5f, -0.5f, z);
            // Vertex v4;
            // v4.pos = float3(0.5f, 0.5f, z);

            // v1.color = v2.color = v3.color = v4.color = float4::One();

            // this->vertex_data_.push_back(v1);
            // this->vertex_data_.push_back(v2);
            // this->vertex_data_.push_back(v3);
            // this->vertex_data_.push_back(v4);

            // this->index_data_.push_back(0);
            // this->index_data_.push_back(3);
            // this->index_data_.push_back(1);

            // this->index_data_.push_back(3);
            // this->index_data_.push_back(2);
            // this->index_data_.push_back(1);

            this->loaded = true;

            return true;
        }
        bool Mesh::HandleNode(const aiNode* node, const aiScene* scene)
        {
            if (node->mNumMeshes > 0)
            {
                auto mesh = scene->mMeshes[node->mMeshes[0]];
                this->HandleMeshNode(mesh, scene);
                return true;
            }

            for (uint32_t c = 0; c < node->mNumChildren; ++c)
            {
                if (this->HandleNode(node->mChildren[c], scene)) return true;
            }

            return false;
        }

        void Mesh::HandleMeshNode(const aiMesh* mesh, const aiScene* scene)
        {
            UNUSED_PARAMETER(scene);

            auto hasPos = mesh->HasPositions();
            auto hasUV = mesh->HasTextureCoords(0);
            auto hasNormal = mesh->HasNormals();

            for (uint32_t i = 0; i < mesh->mNumVertices; ++i)
            {
                Vertex v;
                v.pos = hasPos ? float3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z) : float3(0, 0, 0);
                // v.pos *= 0.2f;
                // v.pos.z() = 0;
                v.normal = hasNormal ? float3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z) : float3(0, 0, 0);
                v.uv = hasUV ? float2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y) : float2(0, 0);
                v.color = float4(1, 1, 1, 1);

                this->vertex_data_.emplace_back(v);
            }

            for (uint32_t i = 0; i < mesh->mNumFaces; ++i)
            {
                auto f = mesh->mFaces[i];
                for (uint32_t fi = 0; fi < f.mNumIndices; ++fi)
                {
                    this->index_data_.emplace_back(f.mIndices[fi]);
                }
            }
        }

        /// Create GPU related buffer
        /// ie. Index/Vertice buffer for rendering
        void Mesh::UpdateGPUBuffer()
        {
            if (this->vertex_buffer_ == nullptr && this->loaded)
            {
                PRINT("Create mesh vertex Buffer");
                GraphicsBufferDescriptor desc;
                desc.type = GraphicsBufferType::GBT_Vertex;
                desc.usage = GraphicsBufferUsage::GBU_GPU_Read_Only;
                desc.offset = 0;
                desc.stride = sizeof(Vertex);
                desc.count = this->vertex_data_.size();
                desc.total_size = desc.count * desc.stride;
                desc.data = this->vertex_data_.data();

                desc.layout.elements_.push_back(ElementLayout::Element("POSITION", DataFormat::DF_RGBFloat));
                desc.layout.elements_.push_back(ElementLayout::Element("NORMAL", DataFormat::DF_RGBFloat));
                desc.layout.elements_.push_back(ElementLayout::Element("UV", DataFormat::DF_RGFloat));
                desc.layout.elements_.push_back(ElementLayout::Element("COLOR", DataFormat::DF_RGBA32));
                desc.layout.topology = ElementTopology::ET_TriangleList;

                this->vertex_buffer_ = Context::GetInstance().GetRenderEngine().Create(desc);
            }

            if (this->index_buffer_ == nullptr && this->loaded)
            {
                PRINT("Create mesh index Buffer");
                GraphicsBufferDescriptor desc;
                desc.type = GraphicsBufferType::GBT_Index;
                desc.usage = GraphicsBufferUsage::GBU_GPU_Read_Only;
                desc.offset = 0;
                desc.stride = sizeof(uint32_t);
                desc.count = this->index_data_.size();
                desc.total_size = desc.count * desc.stride;
                desc.data = this->index_data_.data();
                this->index_buffer_ = Context::GetInstance().GetRenderEngine().Create(desc);
            }
        }
    }  // namespace Core

}  // namespace vEngine