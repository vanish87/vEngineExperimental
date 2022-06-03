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
