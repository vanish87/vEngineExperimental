
/// \file animator.hpp
/// \brief Head file for Animator
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_ANIMATION_ANIMATOR_HPP
#define _VENGINE_ANIMATION_ANIMATOR_HPP

#pragma once

#include <unordered_map>
#include <vector>

#include <engine.hpp>
#include <vengine/core/game_object.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Animation
    {
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class VENGINE_API Animator : public Core::GameObject
        {
            public:
                constexpr static auto properties()
                {
                    return std::tuple_cat(
                        GameObject::properties(),
                        std::make_tuple(
                            property("animations_", &Animator::animations_)
                            // property("inverse_bind_pose_matrix", &Bone::inverse_bind_pose_matrix_)
                        )
                    );
                }
                static AnimatorSharedPtr Default();
                
                /// \brief brief constructor description.
                Animator(const Core::GameObjectType type = Core::GameObjectType::Animator);
                virtual ~Animator() {}

                /// class variable description

                void UpdateLerp(const float dt);

                // void Setup(SkeletonSharedPtr skeleton, std::vector<AnimationClipSharedPtr> animations)
                void SetAnimations(std::vector<AnimationClipSharedPtr> animations);

                std::unordered_map<std::string, JointSharedPtr> GetAnimatedJoints();

                // also State management codes

            private:
                float current_time_;
                std::unordered_map<std::string, JointSharedPtr> current_joints_;

                AnimationClipSharedPtr current_clip_;
                AnimationClipSharedPtr next_clip_;

                std::vector<AnimationClipSharedPtr> animations_;

            public:
                // skeleton is not needed here, animator just lerp clip values
                //  SkeletonSharedPtr skeleton_;
        };

    }  // namespace Animation
}  // namespace vEngine

#endif /* _VENGINE_ANIMATION_ANIMATOR_HPP */
