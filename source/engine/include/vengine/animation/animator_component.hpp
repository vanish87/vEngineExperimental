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
#include <vengine/core/transform_node.hpp>
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

                    // auto joints = animator->GetAnimatedJoints();
					auto joints = animator->current_clip_->joints_;

                    this->Owner()->TraverseAllChildren<BoneComponent>(
                        [&](BoneComponentSharedPtr node)
                        {
                            // node->UpdateLocal(parent);
                            // node->OnUpdate();

							//set bone's Transform to animated TRS
							auto gn = std::dynamic_pointer_cast<Core::TransformNode>(node->Owner());
							JointSharedPtr j = nullptr;
							for(auto joint : joints)
							{
								if(joint->name_ == node->name_)
								{
									j = joint;
									break;
								}
							}
							// auto j = joints[0];

							gn->Transform()->Translate() = j->position_keys_[0].value;
							gn->Transform()->Rotation() = j->rotation_keys_[0].value;
							gn->Transform()->Scale() = j->scale_keys_[0].value;
							// gn->Transform()->Scale() = Core::float3(0.5f, 0.5f, 0.5f);

                            // auto pos = node->game_object_->Translate();
                            // PRINT(pos.x() << " " << pos.y());
                            // PRINT(node->name_);
                            return true;
                        });
                };

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
