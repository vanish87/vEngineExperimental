/// \file animator_component.hpp
/// \brief Head file for Animator Component
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_ANIMATION_ANIMATOR_COMPONENT_HPP
#define _VENGINE_ANIMATION_ANIMATOR_COMPONENT_HPP

#pragma once

#include <engine.hpp>
#include <vengine/core/component.hpp>
#include <vengine/core/transform_component.hpp>
#include <vengine/animation/animator.hpp>
#include <vengine/animation/skeleton_component.hpp>
#include <vengine/animation/bone_component.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Animation
    {

        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class AnimatorComponent : public Core::Component<Animator>
        {
            public:
                /// \brief brief constructor description.
                AnimatorComponent();
                virtual ~AnimatorComponent();
                virtual void OnInit() override
                {
                    this->timer = 0;
                    // auto skeleton = this->FirstOf<SkeletonComponent>();
                    // this->GO()->Setup(skeleton->GO(), std::vector<AnimationClipSharedPtr>());
                };
                virtual void OnUpdate() override
                {
					//1. Search same level to find skeleton/or skeleton already set
					//2. Update Animator to Lerp Animation Clips
					//3. Animator component will update current time TRS for all Bone Node

                    Core::Component<Animator>::OnUpdate();
                    auto animator = this->GO();
                    animator->Lerp();

                    timer += 0.01f;
                    int fid = Math::FloorToInt(timer);
                    // auto fid = 0;

                    // auto joints = animator->GetAnimatedJoints();
                    if (animator->current_clip_ == nullptr) animator->current_clip_ = animator->animations_[0];

                    auto joints = animator->current_clip_->joints_;

                    this->animation_root_->TraverseAllChildren<BoneComponent>(
                        [&](BoneComponentSharedPtr node)
                        {
                            // node->UpdateLocal(parent);
                            // node->OnUpdate();

							//set bone's Transform to animated TRS
							auto transform = node->Owner()->FirstOf<Core::TransformComponent>();
							JointSharedPtr j = nullptr;
							for(auto joint : joints)
							{
								if(joint->name_ == node->name_)
								{
									j = joint;
									break;
								}
							}
                            // if(transform == nullptr || j == nullptr) return true;
							// auto j = joints[0];

                            auto ps = j->position_keys_.size();
                            auto rs = j->rotation_keys_.size();
                            auto ss = j->scale_keys_.size();

							transform->GO()->Translate() = j->position_keys_[fid%ps].value;
							transform->GO()->Rotation() = j->rotation_keys_[fid%rs].value;
							transform->GO()->Scale() = j->scale_keys_[fid%ss].value;
							// gn->Transform()->Scale() = Core::float3(0.5f, 0.5f, 0.5f);

                            // auto pos = node->game_object_->Translate();
                            // PRINT(pos.x() << " " << pos.y());
                            // PRINT(node->name_);
                            return true;
                        });
                };

                float timer;
                Core::GameNodeSharedPtr animation_root_;

            public:
                /// \brief A brief function description.
                ///
                /// \param p1 Description for p1.
                /// \param p2 Description for p2.
                /// \return Description for return value.
                int GetVariable(int p1, float p2);
        };
    }  // namespace Animation

}  // namespace vEngine

#endif /* _VENGINE_ANIMATION_ANIMATOR_COMPONENT_HPP */
