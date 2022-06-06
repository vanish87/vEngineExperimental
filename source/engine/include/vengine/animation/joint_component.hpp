/// \file joint_component.hpp
/// \brief Head file for Joint Component
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_ANIMATION_JOINT_COMPONENT_HPP
#define _VENGINE_ANIMATION_JOINT_COMPONENT_HPP

#pragma once

#include <engine.hpp>
#include <vengine/core/component.hpp>
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
        class JointComponent : public Core::Component<Joint>
        {
            public:
                /// \brief brief constructor description.
                JointComponent();
                virtual ~JointComponent();


                //==============================================
                //Joint Component is not needed


            public:
                /// \brief A brief function description.
                ///
                /// \param p1 Description for p1.
                /// \param p2 Description for p2.
                /// \return Description for return value.
                int GetVariable(int p1, float p2);
        };
    }  // namespace Core

}  // namespace vEngine

#endif /* _VENGINE_ANIMATION_JOINT_COMPONENT_HPP */
