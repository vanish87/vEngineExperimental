/// \file animation_clip.hpp
/// \brief Head file for Animation Clip
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_ANIMATION_ANIMATION_CLIP_HPP
#define _VENGINE_ANIMATION_ANIMATION_CLIP_HPP

#pragma once

#include <engine.hpp>
#include <vengine/core/game_object.hpp>
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
        class AnimationClip : public Core::GameObject
        {
            public:
                /// \brief brief constructor description.
                AnimationClip();
				virtual ~AnimationClip();

                /// class variable description
                float duration_;
				float ticks_per_second_;
                uint32_t total_frame_;

				std::vector<JointSharedPtr> joints_;

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

#endif /* _VENGINE_ANIMATION_ANIMATION_CLIP_HPP */
