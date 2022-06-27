
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

#include <engine.hpp>
#include <vector>
#include <vengine/core/game_object.hpp>
#include <vengine/animation/animation_clip.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Animation
    {
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class Animator : public Core::GameObject
        {
            public:
                /// \brief brief constructor description.
                Animator();

                /// class variable description

                void UpdateLerp(const float dt)
                {
                    UNUSED_PARAMETER(dt);
                    // auto joints = animator->GetAnimatedJoints();
                    if (this->current_clip_ == nullptr) this->current_clip_ = this->animations_[0];

                    // this->current_time_ += dt;
                    //do lerp between
                    // current_clip_ and next_clip_

                    //get a vector of joints
                    this->current_joints_ = this->current_clip_->GetJointAtTime(this->current_time_);

                    //generate pos/rot/scale for each joints
                    //animation clip will update local bone data
                    //bone component's transform will update scene node bone data


                    // foreach joint in skeleton_
                    // {

                    // }
                };
                

                // void Setup(SkeletonSharedPtr skeleton, std::vector<AnimationClipSharedPtr> animations)
                void Setup(std::vector<AnimationClipSharedPtr> animations)
                {
                    // this->skeleton_ = skeleton;
                    this->animations_ = animations;
                }

                std::unordered_map<std::string, JointSharedPtr> GetAnimatedJoints()
                {
                    return this->current_joints_;
                }

                //also State management codes

                float current_time_;
				std::unordered_map<std::string, JointSharedPtr> current_joints_;

                AnimationClipSharedPtr current_clip_;
                AnimationClipSharedPtr next_clip_;

            public:
                std::vector<AnimationClipSharedPtr> animations_;

                //skeleton is not needed here, animator just lerp clip values
                // SkeletonSharedPtr skeleton_;
        };

    }  // namespace Animation
}  // namespace vEngine

#endif /* _VENGINE_ANIMATION_ANIMATOR_HPP */
