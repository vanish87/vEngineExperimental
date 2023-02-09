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
#include <vengine/core/game_object_factory.hpp>
#include <vengine/rendering/render_engine.hpp>
#include <vengine/rendering/graphics_buffer.hpp>
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
            UNUSED_PARAMETER(primitive);
            UNUSED_PARAMETER(sub_div);
            static auto m = GameObjectFactory::Create<GameObjectType::Mesh, Mesh>();
            // if (m->CurrentState() != ResourceState::Loaded)
            // {
            //     switch (primitive)
            //     {
            //         case MeshPrimitive::Cube:
            //             GenerateCube(m);
            //             break;

            //         default:
            //             NOT_IMPL_ASSERT;
            //             break;
            //     }
            // }
            return m;
        }

        /// constructor detailed defintion,
        /// should be 2 lines
        Mesh::Mesh(const GameObjectType type) : GameObject(type), vertex_buffer_{nullptr}, index_buffer_{nullptr}
        {
            // PRINT("mesh object created");
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

        void Mesh::SetVertexData(const std::vector<Vertex> vertices, const std::vector<Index> indices)
        {
            this->vertex_data_ = vertices;
            this->index_data_ = indices;
        }
        void Mesh::SetBoneData(const std::string name, const int id, std::vector<VertexWeight> weights, float4x4 inverse_bind_pose_matrix)
        {
            auto bone = GameObjectFactory::Create<GameObjectType::BoneComponent, Animation::BoneComponent>();
            bone->descriptor_.name = name;
            auto go = bone->GO();
            go->id_ = id;
            go->inverse_bind_pose_matrix_ = inverse_bind_pose_matrix;

            for (auto& w : weights)
            {
                auto vid = w.index;
                auto vweight = w.weight;

                auto& v = this->vertex_data_[vid];
                // statics[vid]++;
                // CHECK_ASSERT(statics[vid] < 8);

                for (uint32_t vcount = 0; vcount < 8; ++vcount)
                {
                    if (vcount < 4)
                    {
                        if (v.bone_id_0[vcount] != -1)
                        {
                            // CHECK_ASSERT(vcount < 3);
                            continue;
                        }

                        v.bone_id_0[vcount] = id;
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

                        v.bone_id_1[index] = id;
                        v.bone_weight_1[index] = vweight;
                        break;
                    }
                }
            }
            CHECK_ASSERT(this->bone_data_.find(bone->descriptor_.name) == this->bone_data_.end());
            this->bone_data_[bone->descriptor_.name] = bone;

            PRINT("Bone " << bone->descriptor_.name << " id " << id);
        }

        /// Create GPU related buffer
        /// ie. Index/Vertice buffer for rendering
        void Mesh::UpdateGPUBuffer()
        {
            if (this->vertex_buffer_ == nullptr)
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

                this->vertex_buffer_ = GameObjectFactory::Create<GameObjectType::GraphicsBuffer, GraphicsBuffer>(desc);
            }

            if (this->index_buffer_ == nullptr)
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
                this->index_buffer_ = GameObjectFactory::Create<GameObjectType::GraphicsBuffer, GraphicsBuffer>(desc);
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

        }
    }  // namespace Core

}  // namespace vEngine