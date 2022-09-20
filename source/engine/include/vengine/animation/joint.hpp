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
        struct VENGINE_API JointKey
        {
                constexpr static auto properties()
                {
                    return std::tuple_cat(
                        std::make_tuple(
                            property("time", &JointKey::time),
                            property("value", &JointKey::value)
                        )
                    );
                }
                float time;
                T value;
                JointKey(float t, const T& val) : time{t}, value{val} {};
                JointKey() : time{0} {};
        };
        /// \brief A brief class description.
        ///
        /// Joint is for animation clip
        /// Bone is for pose-vertex binding
        class VENGINE_API Joint : public Core::GameObject
        {
            public:
                constexpr static auto properties()
                {
                    return std::tuple_cat(
                        GameObject::properties(),
                        std::make_tuple(
                            property("position_keys", &Joint::position_keys_),
                            property("rotation_keys", &Joint::rotation_keys_),
                            property("scale_keys", &Joint::scale_keys_)
                        )
                    );
                }
            public:
                /// \brief brief constructor description.
                Joint();
                virtual ~Joint();

                std::vector<JointKey<Core::float3>> position_keys_;
                std::vector<JointKey<Core::quaternion>> rotation_keys_;
                std::vector<JointKey<Core::float3>> scale_keys_;

                JointKey<Core::float3> PosAtTime(const float time);
                JointKey<Core::quaternion> RotAtTime(const float time);
                JointKey<Core::float3> ScaleAtTime(const float time);

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
