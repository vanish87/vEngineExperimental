

/// \file animator.cpp
/// \brief source file for Animator
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/animation/animator.hpp>
#include <vengine/animation/animation_clip.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Animation
    {

        /// constructor detailed defintion,
        /// should be 2 lines
        Animator::Animator() : current_time_{0} {}
        void Animator::SetAnimations(const std::vector<AnimationClipSharedPtr> animations)
        {
            // this->skeleton_ = skeleton;
            this->animations_ = animations;
        }
        std::unordered_map<std::string, JointSharedPtr> Animator::GetAnimatedJoints()
        {
            return this->current_joints_;
        }
        void Animator::UpdateLerp(const float dt)
        {
            UNUSED_PARAMETER(dt);
            // auto joints = animator->GetAnimatedJoints();
            if (this->current_clip_ == nullptr) this->current_clip_ = this->animations_[0];

            this->current_time_ += dt;
            // do lerp between
            // current_clip_ and next_clip_

            // get a vector of joints
            this->current_joints_ = this->current_clip_->GetJointAtTime(this->current_time_);

            // generate pos/rot/scale for each joints
            // animation clip will update local bone data
            // bone component's transform will update scene node bone data

            // foreach joint in skeleton_
            // {

            // }
        };

    }  // namespace Animation
}  // namespace vEngine