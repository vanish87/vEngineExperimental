/// \file skeleton.hpp
/// \brief Head file for Skeleton
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _LEGACY_CODE_ANIMATION_SKELETON_HPP
#define _LEGACY_CODE_ANIMATION_SKELETON_HPP

#pragma once

#include <vector>
#include <engine.hpp>
#include <vengine/core/game_object.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Animation
    {
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class VENGINE_API Skeleton : public Core::GameObject
        {
            public:
                /// \brief brief constructor description.
                Skeleton();

                /// class variable description
                int public_variable_;

                // std::vector<BoneSharedPtr> GetBoneUpdated()
                // {
                //     return std::vector<BoneSharedPtr>();
                // }

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

#endif /* _LEGACY_CODE_ANIMATION_SKELETON_HPP */
