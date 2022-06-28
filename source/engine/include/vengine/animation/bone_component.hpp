/// \file bone_component.hpp
/// \brief Head file for Bone component
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_ANIMATION_BONE_COMPONENT_HPP
#define _VENGINE_ANIMATION_BONE_COMPONENT_HPP

#pragma once

#include <engine.hpp>
#include <vengine/animation/bone.hpp>
#include <vengine/core/component.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Animation
    {
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class BoneComponent : public Core::Component<Bone>
        {
            public:
                /// \brief brief constructor description.
                BoneComponent();
                virtual ~BoneComponent();

                // void Update()

                /// class variable description
                int public_variable_;

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

#endif /* _VENGINE_ANIMATION_BONE_COMPONENT_HPP */
