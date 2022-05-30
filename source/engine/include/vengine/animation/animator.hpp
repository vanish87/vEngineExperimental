
/// \file animator.hpp
/// \brief Head file for Animator
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_ANIMATION_ANIMATOR_HPP
#define _VENGINE_ANIMATION_ANIMATOR_HPP

#pragma once

#include <engine.hpp>
#include <vector>
#include <vengine/core/game_object.hpp>
#include <vengine/animation/animation_clip.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Animation
    {
        using namespace ::vEngine::Core;
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class Animator : public GameObject
        {
            public:
                /// \brief brief constructor description.
                Animator();

                /// class variable description

            public:
                std::vector<AnimationClip> animations_;
        };

    }  // namespace Animation
}  // namespace vEngine

#endif /* _VENGINE_ANIMATION_ANIMATOR_HPP */
