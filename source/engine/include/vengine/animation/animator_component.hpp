/// \file animator_component.hpp
/// \brief Head file for Animator Component
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_ANIMATION_ANIMATOR_COMPONENT_HPP
#define _VENGINE_ANIMATION_ANIMATOR_COMPONENT_HPP

#pragma once

#include <engine.hpp>
#include <vengine/animation/animator.hpp>
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
        class VENGINE_API AnimatorComponent : public Core::Component<Animator>
        {
            public:
                constexpr static auto properties()
                {
                    return std::tuple_cat(
                        Core::Component<Animator>::properties(), 
                        std::make_tuple(
                            Core::property("animation_root_", &AnimatorComponent::animation_root_)
                        )
                    );
                }
            public:
                /// \brief brief constructor description.
                AnimatorComponent();
                virtual ~AnimatorComponent();
                virtual void OnInit() override;
                virtual void OnUpdate() override;

                void SetAnimationRoot(const Core::GameNodeSharedPtr root);

            private:
                // float timer;
                Core::GameNodeSharedPtr animation_root_;

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

#endif /* _VENGINE_ANIMATION_ANIMATOR_COMPONENT_HPP */
