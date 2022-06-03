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
#include <vengine/core/game_object_factory.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {

        /// constructor detailed defintion,
        /// should be 2 lines
        Mesh::Mesh() : vertex_buffer_{nullptr}, index_buffer_{nullptr}, loaded{false}
        {
            // PRINT("mesh object created");
        }
        Mesh::Mesh(const aiMesh* mesh): vertex_buffer_{nullptr}, index_buffer_{nullptr}, loaded{false}
        {
            this->Load(mesh);
            PRINT("Vertices count " << this->vertex_data_.size() << " indices count " << this->index_data_.size() << " joint count " << this->bone_data_.size());
        }

        Mesh::~Mesh()
        {
            this->vertex_data_.clear();
            this->index_data_.clear();
            this->bone_data_.clear();
        }

        void Mesh::Load(const aiMesh* mesh)
        {
            CHECK_ASSERT_NOT_NULL(mesh);

            auto hasPos = mesh->HasPositions();
            auto hasUV = mesh->HasTextureCoords(0);
            auto hasNormal = mesh->HasNormals();
            // auto hasBones = mesh->HasBones();

            this->vertex_data_.clear();
            this->index_data_.clear();
            this->bone_data_.clear();

            this->name_ = mesh->mName.data;

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
            // if (hasBones)
            {
                for (uint32_t b = 0; b < mesh->mNumBones; ++b)
                {
                    PRINT(mesh->mName.data << " has bones/joint " << mesh->mBones[b]->mName.data << " with " << mesh->mBones[b]->mNumWeights << " weights");
                    // mesh->mBones[b]->mOffsetMatrix will transform vertex from model space to pose/joint local space;
                    // aiBone's document is confusing
                    // https://learnopengl.com/Guest-Articles/2020/Skeletal-Animation is CORRECT
                    auto bone = mesh->mBones[b];

                    GameObjectDescription jdesc;
                    jdesc.type = GameObjectType::Bone;
                    auto joint = GameObjectFactory::Create<Animation::Bone>(jdesc);
                    joint->name_ = bone->mName.data;
                    // joint->inverse_bind_pos_matrix_ = bone->mOffsetMatrix;
                    for (uint32_t wid = 0; wid < bone->mNumWeights; ++wid)
                    {
                        auto aiWeight = bone->mWeights[wid];
                        Animation::VertexWeight w;
                        w.index = aiWeight.mVertexId;
                        w.weight = aiWeight.mWeight;
                        joint->weights.emplace_back(w);
                    }

                    this->bone_data_[joint->name_] = joint;
                }
            }

            this->loaded = true;
        }

        /// Create GPU related buffer
        /// ie. Index/Vertice buffer for rendering
        void Mesh::UpdateGPUBuffer()
        {
            if (this->vertex_buffer_ == nullptr && this->loaded)
            {
                // PRINT("Create mesh vertex Buffer");
                GraphicsBufferDescriptor desc;
                desc.type = GraphicsResourceType::Vertex;
                desc.usage = GraphicsResourceUsage::GPU_Read_Only;
                desc.resource.offset = 0;
                desc.resource.stride = sizeof(Vertex);
                desc.resource.count = this->vertex_data_.size();
                desc.resource.total_size = desc.resource.count * desc.resource.stride;
                desc.resource.data = this->vertex_data_.data();

                desc.layout.elements_.push_back(ElementLayout::Element("POSITION", DataFormat::RGBFloat));
                desc.layout.elements_.push_back(ElementLayout::Element("NORMAL", DataFormat::RGBFloat));
                desc.layout.elements_.push_back(ElementLayout::Element("UV", DataFormat::RGFloat));
                desc.layout.elements_.push_back(ElementLayout::Element("COLOR", DataFormat::RGBA32));
                desc.layout.topology = ElementTopology::TriangleList;

                this->vertex_buffer_ = Context::GetInstance().GetRenderEngine().Create(desc);
            }

            if (this->index_buffer_ == nullptr && this->loaded)
            {
                // PRINT("Create mesh index Buffer");
                GraphicsBufferDescriptor desc;
                desc.type = GraphicsResourceType::Index;
                desc.usage = GraphicsResourceUsage::GPU_Read_Only;
                desc.resource.offset = 0;
                desc.resource.stride = sizeof(uint32_t);
                desc.resource.count = this->index_data_.size();
                desc.resource.total_size = desc.resource.count * desc.resource.stride;
                desc.resource.data = this->index_data_.data();
                this->index_buffer_ = Context::GetInstance().GetRenderEngine().Create(desc);
            }
        }
    }  // namespace Core

}  // namespace vEngine