
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

                void Lerp()
                {
                    //do lerp between
                    // current_clip_ and next_clip_

                    //get a vector of joints
                    auto joints = this->current_clip_->GetJointAtTime(this->current_time_);

                    //generate pos/rot/scale for each joints
                    //animation clip will update local bone data
                    //bone component's transform will update scene node bone data


                    // foreach joint in skeleton_
                    // {

                    // }
                };
                

                void Setup(SkeletonSharedPtr skeleton, std::vector<AnimationClipSharedPtr> animations)
                {
                    this->skeleton_ = skeleton;
                    this->animations_ = animations;
                }

                std::vector<JointSharedPtr> GetAnimatedJoints()
                {
                    return std::vector<JointSharedPtr>();
                }

                //also State management codes

                float current_time_;
                AnimationClipSharedPtr current_clip_;
                AnimationClipSharedPtr next_clip_;

            public:
                std::vector<AnimationClipSharedPtr> animations_;

                //skeleton is not needed here, animator just lerp clip values
                SkeletonSharedPtr skeleton_;
        };

    }  // namespace Animation
}  // namespace vEngine

#endif /* _VENGINE_ANIMATION_ANIMATOR_HPP */
