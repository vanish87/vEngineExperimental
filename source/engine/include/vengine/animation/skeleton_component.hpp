/// \file skeleton_component.hpp
/// \brief Head file for Skeleton Component
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_ANIMATION_SKELETON_COMPONENT_HPP
#define _VENGINE_ANIMATION_SKELETON_COMPONENT_HPP

#pragma once

#include <engine.hpp>
#include <vengine/core/component.hpp>
#include <vengine/animation/skeleton.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Animation
    {
		using namespace Core;
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class SkeletonComponent : public Component<Skeleton>
        {
            public:
                /// \brief brief constructor description.
                SkeletonComponent();
                virtual ~SkeletonComponent();

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

#endif /* _VENGINE_ANIMATION_SKELETON_COMPONENT_HPP */
