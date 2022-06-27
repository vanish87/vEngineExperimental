/// \file animation_clip.hpp
/// \brief Head file for Animation Clip
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_ANIMATION_ANIMATION_CLIP_HPP
#define _VENGINE_ANIMATION_ANIMATION_CLIP_HPP

#pragma once

#include <unordered_map>

#include <engine.hpp>
#include <vengine/core/game_object.hpp>
#include <vengine/animation/joint.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Animation
    {

        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class AnimationClip : public Core::GameObject
        {
            public:
                /// \brief brief constructor description.
                AnimationClip();
				virtual ~AnimationClip();


                std::unordered_map<std::string, JointSharedPtr> GetJointAtTime(const float currentTime)
                {
                    // this->current_joint_->position_keys_[0].time = currentTime;
                    // this->current_joint_->position_keys_[0].value = currentTime;
                    auto total =Math::CeilToInt(this->duration_);
                    auto clip_time = currentTime > total ? currentTime - (total * (int)(currentTime / total)) : currentTime;

                    for(const auto& j : this->joints_)
                    {
                        if(this->current_joints_.find(j->name_) == this->current_joints_.end())
                        {
                            this->current_joints_[j->name_] = std::make_shared<Joint>();
                            this->current_joints_[j->name_]->position_keys_.emplace_back(0.0f, Core::float3::Zero());
                            this->current_joints_[j->name_]->rotation_keys_.emplace_back(0.0f, Core::quaternion::Identity());
                            this->current_joints_[j->name_]->scale_keys_.emplace_back(0.0f, Core::float3::One());
                        }
                        // auto current_key = 
                        this->current_joints_[j->name_]->position_keys_[0] = j->PosAtTime(clip_time);
                        this->current_joints_[j->name_]->rotation_keys_[0] = j->RotAtTime(clip_time);
                        this->current_joints_[j->name_]->scale_keys_[0] = j->ScaleAtTime(clip_time);

                    }
                    return this->current_joints_;
                }


                // void Update(const float currentTime)
                // {
                //     //update all Joints with currentTime
                //     for(const auto& j : this->joints_)
                //     {

                //     }
                // }

                /// class variable description
                float duration_;
				float ticks_per_second_;
                uint32_t total_frame_;

                std::unordered_map<std::string, JointSharedPtr> current_joints_;

                //a.k.a channel for animation clips
				std::vector<JointSharedPtr> joints_;

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

#endif /* _VENGINE_ANIMATION_ANIMATION_CLIP_HPP */
