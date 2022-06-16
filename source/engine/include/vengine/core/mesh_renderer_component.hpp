/// \file mesh_renderer_component.hpp
/// \brief Head file for Mesh Renderer Component
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_MESH_RENDERER_COMPONENT_HPP
#define _VENGINE_CORE_MESH_RENDERER_COMPONENT_HPP

#include <cstring>
#include <vengine/core/component.hpp>
#include <vengine/core/mesh_renderer.hpp>
#include <vengine/core/mesh_component.hpp>
#include <vengine/core/transform_component.hpp>
#include <vengine/rendering/graphics_buffer.hpp>

#include <vengine/core/context.hpp>
#include <vengine/rendering/render_engine.hpp>
#include <vengine/rendering/shared/data_cbuffer.hpp>
#include <vengine/animation/skeleton_component.hpp>
#include <vengine/animation/bone_component.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Rendering
    {
        using namespace vEngine::Core;
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class MeshRendererComponent : public Component<MeshRenderer>
        {
            public:
                /// \brief brief constructor description.
                MeshRendererComponent();

                void OnBeginRender()
                {
                    vEngineObjectConstantBuffer cb;
                    auto mesh = this->GO()->renderable_;
                    if(mesh->skeleton_ != nullptr)
                    {
                        auto skeleton = mesh->skeleton_->FirstOf<Animation::SkeletonComponent>();

                        auto bones = skeleton->GetBones();
                        // auto count = 0;
                        for (const auto& b : bones)
                        {
                            if(mesh->bone_data_.find(b->name_) == mesh->bone_data_.end()) 
                            {
                                GameObjectDescription jdesc;
                                jdesc.type = GameObjectType::Bone;
                                auto new_bone = GameObjectFactory::Create<Animation::Bone>(jdesc);
                                new_bone->name_ = b->name_;
                                new_bone->id_ = static_cast<int>(mesh->bone_data_.size());
                                new_bone->inverse_bind_pose_matrix_ = float4x4::Identity();
                                mesh->bone_data_[b->name_] = new_bone;
                                PRINT_AND_BREAK("Missing bone");
                            }

                            auto transform = b->Owner()->FirstOf<TransformComponent>();
                            auto bone_matrix = transform->GO()->LocalToWorldTransform();
                            auto bone_go = mesh->bone_data_[b->name_];
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


                    Context::GetInstance().GetRenderEngine().OnBind(this->mesh_constant_buffer_);

                }

                virtual void OnUpdate() override
                {
                    //Update local to world matrix for current game node
                    // PRINT("MeshRendererComponent Update");
                    if(this->GO()->renderable_ == nullptr)
                    {
                        auto meshComponent = this->Owner()->FirstOf<MeshComponent>();
                        this->GO()->renderable_ = meshComponent->GO();
                    }
                };

                //world matrix etc.
                GraphicsBufferSharedPtr mesh_constant_buffer_;
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_MESH_RENDERER_COMPONENT_HPP */
