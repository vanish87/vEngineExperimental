/// \file skeleton_component.hpp
/// \brief Head file for Skeleton Component
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_ANIMATION_SKELETON_COMPONENT_HPP
#define _VENGINE_ANIMATION_SKELETON_COMPONENT_HPP

#pragma once

#include <engine.hpp>
#include <vengine/core/component.hpp>
#include <vengine/animation/skeleton.hpp>
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
        class SkeletonComponent : public Core::Component<Skeleton>
        {
            public:
                /// \brief brief constructor description.
                SkeletonComponent();
                virtual ~SkeletonComponent();

                virtual void OnUpdate() override
                {
                    // auto skeleton = this->GO();

                    // ==============
                    // this is done in Animator component
                    // auto boneList = skeleton->GetBoneUpdated();

                    // this->TraverseAllChildren<BoneComponent>(
                    //     [&](BoneComponentSharedPtr bone)
                    //     {
                    //         // node->UpdateLocal(parent);
                    //         // node->OnUpdate();
                    //         auto transform = bone->Owner()->FirstOf<TransformComponent>();

                    //         // auto pos = node->game_object_->Translate();
                    //         // PRINT(pos.x() << " " << pos.y());
                    //         // PRINT(node->name_);
                    //         return true;
                    //     });
                }

                std::vector<BoneComponentSharedPtr> GetBones()
                {
                    if (this->current_bone_list_.size() == 0)
                    {
                        this->Owner()->TraverseAllChildren<BoneComponent>(
                            [&](BoneComponentSharedPtr node)
                            {
                                this->current_bone_list_.push_back(node);
                                return true;
                            });
                    }

                    return this->current_bone_list_;
                }

                std::vector<BoneComponentSharedPtr> current_bone_list_;

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

#endif /* _VENGINE_ANIMATION_SKELETON_COMPONENT_HPP */
