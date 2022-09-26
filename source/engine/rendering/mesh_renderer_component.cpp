/// \file mesh_renderer_component.cpp
/// \brief source file for Mesh Renderer Component
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/rendering/mesh_renderer_component.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Rendering
    {
        using namespace Core;

        /// constructor detailed defintion,
        /// should be 2 lines
        MeshRendererComponent::MeshRendererComponent(const GameObjectType type) : Component(type)
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

            this->mesh_constant_buffer_ = Context::GetInstance().GetRenderEngine()->Create(cbuffer_desc);
        }
        void MeshRendererComponent::OnBeginRender()
        {
            vEngineObjectConstantBuffer cb;
            auto mesh = this->GO()->renderable_;
            // if(mesh->skeleton_ != nullptr)
            {
                // auto skeleton = mesh->skeleton_->FirstOf<Animation::SkeletonComponent>();

                // auto bones = mesh->bone_data_;
                // auto count = 0;
                for (const auto& b : mesh->bone_data_)
                {
                    // if(mesh->bone_data_.find(b->name_) == mesh->bone_data_.end())
                    // {
                    //     continue;
                    //     // GameObjectDescription jdesc;
                    //     // jdesc.type = GameObjectType::Bone;
                    //     // auto new_bone = GameObjectFactory::Create<Animation::Bone>(jdesc);
                    //     // new_bone->name_ = b->name_;
                    //     // new_bone->id_ = static_cast<int>(mesh->bone_data_.size());
                    //     // new_bone->inverse_bind_pose_matrix_ = float4x4::Identity();
                    //     // mesh->bone_data_[b->name_] = new_bone;
                    //     // PRINT_AND_BREAK("Missing bone " << b->name_);
                    // }

                    auto bone = b.second;
                    auto transform = bone->Owner()->FirstOf<TransformComponent>();
                    auto bone_matrix = transform->GO()->LocalToWorldTransform();
                    auto bone_go = bone->GO();
                    auto offset = bone_go->inverse_bind_pose_matrix_;

                    cb.bone[bone_go->id_] = offset * bone_matrix;
                }
            }

            auto trans = this->Owner()->FirstOf<TransformComponent>();
            cb.local_to_world_matrix = trans->GO()->LocalToWorldTransform();
            // cb.local_to_world_matrix = this->Transform()->LocalToWorldTransform();
            // Math::Translate(cb.local_to_world_matrix, 0, 0, 1);
            // cb.local_to_world_matrix[0][0] = 0.1f;
            // cb.local_to_world_matrix[1][1] = 0.1f;
            // cb.local_to_world_matrix[2][2] = 0.1f;
            // cb.local_to_world_matrix[3][2] = 1;
            // cb.local_to_world_matrix = Math::Transpose(cb.local_to_world_matrix);
            // PRINT(cb.local_to_world_matrix[0][0]);
            // PRINT(cb.local_to_world_matrix[1][1]);
            // PRINT(cb.local_to_world_matrix[2][2]);

            auto data = this->mesh_constant_buffer_->Map();
            std::memcpy(data.data, &cb, sizeof(vEngineObjectConstantBuffer));
            this->mesh_constant_buffer_->Unmap();

            Context::GetInstance().GetRenderEngine()->OnBind(this->mesh_constant_buffer_);
        };

        void MeshRendererComponent::OnUpdate()
        {
            // Update local to world matrix for current game node
            //  PRINT("MeshRendererComponent Update");
            if (this->GO()->renderable_ == nullptr)
            {
                auto meshComponent = this->Owner()->FirstOf<MeshComponent>();
                this->GO()->renderable_ = meshComponent->GO();
            }
        };

    }  // namespace Rendering

}  // namespace vEngine