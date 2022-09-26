
/// \file joint.cpp
/// \brief source file for Joint
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/animation/joint.hpp>
#include <vengine/core/quaternion.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Animation
    {

        /// constructor detailed defintion,
        /// should be 2 lines
        Joint::Joint(const Core::GameObjectType type) : GameObject(type) {}
        Joint::~Joint() {}
        JointKey<Core::float3> Joint::PosAtTime(const float time)
        {
            JointKey<Core::float3> current(0, Core::float3::Zero());
            JointKey<Core::float3> next(0, Core::float3::Zero());
            auto size = this->position_keys_.size();
            for (uint32_t i = 0; i < size; ++i)
            {
                current = this->position_keys_[i];
                if (current.time > time)
                {
                    next = this->position_keys_[(i + 1) % size];
                    auto t = (time - current.time) / (next.time - current.time);
                    auto pos = Math::Lerp(current.value, next.value, t);
                    // return JointKey<Core::float3>(time, current.value);
                    return JointKey<Core::float3>(time, pos);
                }
            }

            PRINT_AND_BREAK("Not found");
            return current;
        }
        JointKey<Core::quaternion> Joint::RotAtTime(const float time)
        {
            JointKey<Core::quaternion> current(0, Core::quaternion::Identity());
            JointKey<Core::quaternion> next(0, Core::quaternion::Identity());
            auto size = this->rotation_keys_.size();
            for (uint32_t i = 0; i < size; ++i)
            {
                current = this->rotation_keys_[i];
                if (current.time > time)
                {
                    next = this->rotation_keys_[(i + 1) % size];
                    auto t = (time - current.time) / (next.time - current.time);
                    auto rot = Math::NLerp(current.value, next.value, t);
                    // return JointKey<Core::quaternion>(time, current.value);
                    return JointKey<Core::quaternion>(time, rot);
                }
            }
            PRINT_AND_BREAK("Not found");
            return current;
        }
        JointKey<Core::float3> Joint::ScaleAtTime(const float time)
        {
            JointKey<Core::float3> current(0, Core::float3::One());
            JointKey<Core::float3> next(0, Core::float3::One());
            auto size = this->scale_keys_.size();
            for (uint32_t i = 0; i < size; ++i)
            {
                current = this->scale_keys_[i];
                if (current.time > time)
                {
                    next = this->scale_keys_[(i + 1) % size];
                    auto t = (time - current.time) / (next.time - current.time);
                    auto scale = Math::Lerp(current.value, next.value, t);
                    // return JointKey<Core::float3>(time, current.value);
                    return JointKey<Core::float3>(time, scale);
                }
            }
            // PRINT_AND_BREAK("Not found");
            return current;
        }

        /// A detailed function description, it
        /// should be 2 lines at least.
        int Joint::GetVariable(int p1, float p2)
        {
            UNUSED_PARAMETER(p1);
            UNUSED_PARAMETER(p2);
            return 1;
        }

    }  // namespace Animation
}  // namespace vEngine