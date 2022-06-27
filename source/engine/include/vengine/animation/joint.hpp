/// \file joint.hpp
/// \brief Head file for Joint
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_ANIMATION_JOINT_HPP
#define _VENGINE_ANIMATION_JOINT_HPP

#pragma once

#include <engine.hpp>
#include <vector>
#include <vengine/core/game_object.hpp>
#include <vengine/core/quaternion.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Animation
    {
        template <typename T>
        struct JointKey
        {
                float time;
                T value;
                JointKey(float t, const T& val) : time{t}, value{val} {};
        };
        /// \brief A brief class description.
        ///
        /// Joint is for animation clip
        /// Bone is for pose-vertex binding
        class Joint : public Core::GameObject
        {
            public:
                /// \brief brief constructor description.
                Joint();
                virtual ~Joint();

                std::vector<JointKey<Core::float3>> position_keys_;
                std::vector<JointKey<Core::quaternion>> rotation_keys_;
                std::vector<JointKey<Core::float3>> scale_keys_;

                JointKey<Core::float3> PosAtTime(const float time)
                {
                    JointKey<Core::float3> current(0, Core::float3::Zero());
                    JointKey<Core::float3> next(0, Core::float3::Zero());
                    for (uint32_t i = 0; i < this->position_keys_.size()-1; ++i)
                    {
                        current = this->position_keys_[i];
                        if (current.time > time)
                        {
                            next = this->position_keys_[i+1];
                            auto t = (time - current.time) / (next.time - current.time);
                            auto pos = Math::Lerp(current.value, next.value, t);
                            return JointKey<Core::float3>(time, current.value);
                            // return JointKey<Core::float3>(time, pos);
                        }
                    }

                    PRINT_AND_BREAK("Not found");
                    return current;
                }
                JointKey<Core::quaternion> RotAtTime(const float time)
                {
                    JointKey<Core::quaternion> current(0, Core::quaternion::Identity());
                    JointKey<Core::quaternion> next(0, Core::quaternion::Identity());
                    for (uint32_t i = 0; i < this->rotation_keys_.size()-1; ++i)
                    {
                        current = this->rotation_keys_[i];
                        if (current.time > time)
                        {
                            next = this->rotation_keys_[i+1];
                            auto t = (time - current.time) / (next.time - current.time);
                            auto rot = Math::Lerp(current.value, next.value, t);
                            return JointKey<Core::quaternion>(time, current.value);
                            // return JointKey<Core::quaternion>(time, rot);
                        }
                    }
                    PRINT_AND_BREAK("Not found");
                    return current;
                }
                JointKey<Core::float3> ScaleAtTime(const float time)
                {
                    JointKey<Core::float3> current(0, Core::float3::One());
                    JointKey<Core::float3> next(0, Core::float3::One());
                    for (uint32_t i = 0; i < this->scale_keys_.size()-1; ++i)
                    {
                        current = this->scale_keys_[i];
                        if (current.time > time)
                        {
                            next = this->scale_keys_[i+1];
                            auto t = (time - current.time) / (next.time - current.time);
                            auto scale = Math::Lerp(current.value, next.value, t);
                            return JointKey<Core::float3>(time, current.value);
                            // return JointKey<Core::float3>(time, scale);
                        }
                    }
                    // PRINT_AND_BREAK("Not found");
                    return current;
                }

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

#endif /* _VENGINE_ANIMATION_JOINT_HPP */
