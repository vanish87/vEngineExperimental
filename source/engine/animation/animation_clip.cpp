
/// \file animation_clip.cpp
/// \brief source file for Animation Clip
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/animation/animation_clip.hpp>
#include <vengine/animation/joint.hpp>
#include <vengine/core/vector.hpp>
#include <vengine/core/math.hpp>
#include <vengine/core/quaternion.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Animation
    {
        using namespace Math;
        using namespace Core;

        /// constructor detailed defintion,
        /// should be 2 lines
        AnimationClip::AnimationClip(const GameObjectType type) : duration_{0}, ticks_per_second_{0}, total_frame_{0}
        {
            // this->duration_ = 0;
            // this->current_joint_ = std::make_shared<Joint>();
            // this->current_joint_->position_keys_.emplace_back(0, Core::float3(0, 0, 0));
            // this->current_joint_->rotation_keys_.emplace_back(0, Core::quaternion::Identity());
            // this->current_joint_->scale_keys_.emplace_back(0, Core::float3(1, 1, 1));
        }
        AnimationClip::~AnimationClip() {}
        float& AnimationClip::Duration()
        {
            return this->duration_;
        }
        float& AnimationClip::TicksPerSecond()
        {
            return this->ticks_per_second_;
        }
        uint32_t& AnimationClip::TotalFrame()
        {
            return this->total_frame_;
        }
        std::unordered_map<std::string, JointSharedPtr> AnimationClip::GetJointAtTime(const float currentTime)
        {
            // this->current_joint_->position_keys_[0].time = currentTime;
            // this->current_joint_->position_keys_[0].value = currentTime;
            auto total = CeilToInt(this->duration_);
            auto clip_time = currentTime > total ? currentTime - (total * (int)(currentTime / total)) : currentTime;

            for (const auto& j : this->joints_)
            {
                if (this->current_joints_.find(j.first) == this->current_joints_.end())
                {
                    this->current_joints_[j.first] = std::make_shared<Joint>();
                    this->current_joints_[j.first]->position_keys_.emplace_back(0.0f, float3::Zero());
                    this->current_joints_[j.first]->rotation_keys_.emplace_back(0.0f, quaternion::Identity());
                    this->current_joints_[j.first]->scale_keys_.emplace_back(0.0f, float3::One());
                }
                // auto current_key =
                this->current_joints_[j.first]->position_keys_[0] = j.second->PosAtTime(clip_time);
                this->current_joints_[j.first]->rotation_keys_[0] = j.second->RotAtTime(clip_time);
                this->current_joints_[j.first]->scale_keys_[0] = j.second->ScaleAtTime(clip_time);
            }
            return this->current_joints_;
        }
        void AnimationClip::AddJoint(const std::string& joint_name, const JointSharedPtr joint)
        {
            CHECK_ASSERT(this->joints_.find(joint_name) == this->joints_.end());
            this->joints_[joint_name] = joint;
        }

        /// A detailed function description, it
        /// should be 2 lines at least.
        int AnimationClip::GetVariable(int p1, float p2)
        {
            UNUSED_PARAMETER(p1);
            UNUSED_PARAMETER(p2);
            return 1;
        }

    }  // namespace Animation
}  // namespace vEngine