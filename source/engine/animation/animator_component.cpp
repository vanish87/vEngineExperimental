
/// \file animator_component.cpp
/// \brief source file for Animator Component
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/animation/animator_component.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Animation
    {

        /// constructor detailed defintion,
        /// should be 2 lines
        AnimatorComponent::AnimatorComponent()
        {
            timer = 0;
        }
        AnimatorComponent::~AnimatorComponent() {}

        /// A detailed function description, it
        /// should be 2 lines at least.
        int AnimatorComponent::GetVariable(int p1, float p2)
        {
            UNUSED_PARAMETER(p1);
            UNUSED_PARAMETER(p2);
            return 1;
        }

    }  // namespace Core
}  // namespace vEngine