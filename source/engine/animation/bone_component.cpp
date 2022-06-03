
/// \file joint_component.cpp
/// \brief source file for Joint Component
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/animation/bone_component.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Animation
    {

        /// constructor detailed defintion,
        /// should be 2 lines
        BoneComponent::BoneComponent() {}
        BoneComponent::~BoneComponent() {}

        /// A detailed function description, it
        /// should be 2 lines at least.
        int BoneComponent::GetVariable(int p1, float p2)
        {
            UNUSED_PARAMETER(p1);
            UNUSED_PARAMETER(p2);
            return 1;
        }

    }  // namespace Core
}  // namespace vEngine