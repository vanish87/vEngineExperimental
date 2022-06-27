
/// \file animation_clip.cpp
/// \brief source file for Animation Clip
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/animation/animation_clip.hpp>
#include <vengine/core/vector.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Animation
    {

        /// constructor detailed defintion,
        /// should be 2 lines
        AnimationClip::AnimationClip()
        {
            this->duration_ = 0;
            // this->current_joint_ = std::make_shared<Joint>();
            // this->current_joint_->position_keys_.emplace_back(0, Core::float3(0, 0, 0));
            // this->current_joint_->rotation_keys_.emplace_back(0, Core::quaternion::Identity());
            // this->current_joint_->scale_keys_.emplace_back(0, Core::float3(1, 1, 1));
        }
        AnimationClip::~AnimationClip() {}

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