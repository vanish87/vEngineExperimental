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
#include <vengine/core/game_node_factory.hpp>
#include <vengine/animation/bone_component.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {
        using namespace Rendering;

        MeshSharedPtr Mesh::Default(const MeshPrimitive primitive, const int sub_div)
        {
            // UNUSED_PARAMETER(primitive);
            UNUSED_PARAMETER(sub_div);
            static auto m = std::make_shared<Mesh>();
            if (m->CurrentState() != ResourceState::Loaded)
            {
                switch (primitive)
                {
                    case MeshPrimitive::Cube:
                        GenerateCube(m);
                        break;

                    default:
                        NOT_IMPL_ASSERT;
                        break;
                }
            }
            return m;
        }
        bool Mesh::Load(const ResourceDescriptorSharedPtr desc)
        {
            return false;
        }
        ResourceState Mesh::CurrentState()
        {
            return this->current_state_;
        }

        /// constructor detailed defintion,
        /// should be 2 lines
        Mesh::Mesh() : vertex_buffer_{nullptr}, index_buffer_{nullptr}
        {
            // PRINT("mesh object created");
        }
        Mesh::Mesh(const aiMesh* mesh) : vertex_buffer_{nullptr}, index_buffer_{nullptr}
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

        MeshSharedPtr Default()
        {
            static auto m = std::make_shared<Mesh>();
            return m;
        }

        float4x4 Mesh::AiMatrixToFloat4x4(aiMatrix4x4 mat)
        {
            return Math::Transpose(float4x4(mat[0][0], mat[0][1], mat[0][2], mat[0][3], mat[1][0], mat[1][1], mat[1][2], mat[1][3], mat[2][0], mat[2][1], mat[2][2], mat[2][3], mat[3][0], mat[3][1],
                                            mat[3][2], mat[3][3]));
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

                v.bone_id_0 = v.bone_id_1 = int4(-1, -1, -1, -1);
                v.bone_weight_0 = v.bone_weight_1 = float4::Zero();

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
                std::unordered_map<int, int> statics;
                for (uint32_t b = 0; b < mesh->mNumBones; ++b)
                {
                    PRINT(mesh->mName.data << " has bones/joint " << mesh->mBones[b]->mName.data << " with " << mesh->mBones[b]->mNumWeights << " weights");
                    // mesh->mBones[b]->mOffsetMatrix will transform vertex from model space to pose/joint local space;
                    // aiBone's document is confusing
                    // https://learnopengl.com/Guest-Articles/2020/Skeletal-Animation is CORRECT
                    auto ai_bone = mesh->mBones[b];

                    ComponentDescription bdesc;
                    bdesc.type = ComponentType::Bone;
                    auto comp = GameNodeFactory::Create<Animation::BoneComponent>(bdesc);
                    auto bone = comp->GO();
                    bone->name_ = ai_bone->mName.data;
                    comp->name_ = ai_bone->mName.data;
                    bone->id_ = b;
                    bone->inverse_bind_pose_matrix_ = this->AiMatrixToFloat4x4(ai_bone->mOffsetMatrix);

                    for (uint32_t wid = 0; wid < ai_bone->mNumWeights; ++wid)
                    {
                        auto aiWeight = ai_bone->mWeights[wid];
                        Animation::VertexWeight w;
                        w.index = aiWeight.mVertexId;
                        w.weight = aiWeight.mWeight;
                        bone->weights.emplace_back(w);

                        auto vid = w.index;
                        auto vweight = w.weight;

                        auto& v = this->vertex_data_[vid];
                        statics[vid]++;
                        CHECK_ASSERT(statics[vid] < 8);

                        for (uint32_t vcount = 0; vcount < 8; ++vcount)
                        {
                            if (vcount < 4)
                            {
                                if (v.bone_id_0[vcount] != -1)
                                {
                                    // CHECK_ASSERT(vcount < 3);
                                    continue;
                                }

                                v.bone_id_0[vcount] = b;
                                v.bone_weight_0[vcount] = vweight;
                                break;
                            }
                            else
                            {
                                auto index = vcount % 4;
                                if (v.bone_id_1[index] != -1)
                                {
                                    // CHECK_ASSERT(vcount < 3);
                                    continue;
                                }

                                v.bone_id_1[index] = b;
                                v.bone_weight_1[index] = vweight;
                                break;
                            }
                        }
                    }

                    CHECK_ASSERT(this->bone_data_.find(bone->name_) == this->bone_data_.end());
                    this->bone_data_[bone->name_] = comp;

                    PRINT("Bone " << bone->name_ << " id " << bone->id_);
                }
                auto max = 0;
                for (auto& s : statics) max = Math::Max(max, s.second);
                PRINT("max vertex count for blend " << max);
            }

            this->current_state_ = ResourceState::Loaded;
        }

        /// Create GPU related buffer
        /// ie. Index/Vertice buffer for rendering
        void Mesh::UpdateGPUBuffer()
        {
            if (this->vertex_buffer_ == nullptr && this->CurrentState() == ResourceState::Loaded)
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

                // Not used
                desc.layout.elements_.push_back(ElementLayout::Element("POSITION", DataFormat::RGBFloat));
                desc.layout.elements_.push_back(ElementLayout::Element("NORMAL", DataFormat::RGBFloat));
                desc.layout.elements_.push_back(ElementLayout::Element("UV", DataFormat::RGFloat));
                desc.layout.elements_.push_back(ElementLayout::Element("COLOR", DataFormat::RGBA32));
                desc.layout.elements_.push_back(ElementLayout::Element("BLENDINDICES", DataFormat::RGBAInt));
                desc.layout.elements_.push_back(ElementLayout::Element("BLENDWEIGHT", DataFormat::RGBAFloat));
                desc.layout.topology = ElementTopology::TriangleList;

                this->vertex_buffer_ = Context::GetInstance().GetRenderEngine().Create(desc);
            }

            if (this->index_buffer_ == nullptr && this->CurrentState() == ResourceState::Loaded)
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

        void Mesh::GenerateCube(MeshSharedPtr mesh)
        {
            mesh->vertex_data_.clear();
            mesh->index_data_.clear();

            if (mesh->vertex_buffer_ != nullptr) mesh->vertex_buffer_.reset();
            if (mesh->index_buffer_ != nullptr) mesh->index_buffer_.reset();

            Vertex v0;
            v0.pos = float3(0.5f, 0.5f, 0.5f);
            v0.normal = float3(0, 0, -1);
            v0.uv = float2(1, 1);

            Vertex v1;
            v1.pos = float3(-0.5f, 0.5f, 0.5f);
            v1.normal = float3(0, 0, -1);
            v1.uv = float2(0, 1);

            Vertex v2;
            v2.pos = float3(-0.5f, -0.5f, 0.5f);
            v2.normal = float3(0, 0, -1);
            v2.uv = float2(0, 0);

            Vertex v3;
            v3.pos = float3(0.5f, -0.5f, 0.5f);
            v3.normal = float3(0, 0, -1);
            v3.uv = float2(1, 0);

            Vertex v4;
            v4.pos = float3(0.5f, 0.5f, -0.5f);
            v4.normal = float3(0, 0, -1);
            v4.uv = float2(1, 0);
            Vertex v5;
            v5.pos = float3(-0.5f, 0.5f, -0.5f);
            v5.normal = float3(0, 0, -1);
            v5.uv = float2(1, 0);
            Vertex v6;
            v6.pos = float3(-0.5f, -0.5f, -0.5f);
            v6.normal = float3(0, 0, -1);
            v6.uv = float2(1, 0);
            Vertex v7;
            v7.pos = float3(0.5f, -0.5f, -0.5f);
            v7.normal = float3(0, 0, -1);
            v7.uv = float2(1, 0);

            mesh->vertex_data_.push_back(v0);
            mesh->vertex_data_.push_back(v1);
            mesh->vertex_data_.push_back(v2);
            mesh->vertex_data_.push_back(v3);
            mesh->vertex_data_.push_back(v4);
            mesh->vertex_data_.push_back(v5);
            mesh->vertex_data_.push_back(v6);
            mesh->vertex_data_.push_back(v7);

            mesh->index_data_.push_back(0);
            mesh->index_data_.push_back(2);
            mesh->index_data_.push_back(1);

            mesh->index_data_.push_back(0);
            mesh->index_data_.push_back(3);
            mesh->index_data_.push_back(2);

            mesh->index_data_.push_back(4);
            mesh->index_data_.push_back(5);
            mesh->index_data_.push_back(6);

            mesh->index_data_.push_back(4);
            mesh->index_data_.push_back(6);
            mesh->index_data_.push_back(7);

            mesh->index_data_.push_back(0);
            mesh->index_data_.push_back(4);
            mesh->index_data_.push_back(3);

            mesh->index_data_.push_back(3);
            mesh->index_data_.push_back(4);
            mesh->index_data_.push_back(7);

            mesh->index_data_.push_back(5);
            mesh->index_data_.push_back(1);
            mesh->index_data_.push_back(6);

            mesh->index_data_.push_back(1);
            mesh->index_data_.push_back(6);
            mesh->index_data_.push_back(2);

            mesh->index_data_.push_back(0);
            mesh->index_data_.push_back(1);
            mesh->index_data_.push_back(5);

            mesh->index_data_.push_back(0);
            mesh->index_data_.push_back(5);
            mesh->index_data_.push_back(4);

            mesh->index_data_.push_back(2);
            mesh->index_data_.push_back(3);
            mesh->index_data_.push_back(6);

            mesh->index_data_.push_back(3);
            mesh->index_data_.push_back(7);
            mesh->index_data_.push_back(6);

            mesh->current_state_ = ResourceState::Loaded;
        }
    }  // namespace Core

}  // namespace vEngine