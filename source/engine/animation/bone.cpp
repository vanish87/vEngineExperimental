
/// \file bone.cpp
/// \brief source file for Bone
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/animation/bone.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Animation
    {
        /// constructor detailed defintion,
        /// should be 2 lines
        Bone::Bone() : GameObject(Core::GameObjectType::Bone),id_(-1) {}

        /// A detailed function description, it
        /// should be 2 lines at least.
        int Bone::GetVariable(int p1, float p2)
        {
            UNUSED_PARAMETER(p1);
            UNUSED_PARAMETER(p2);
            return 1;
        }

    }  // namespace Animation
}  // namespace vEngine