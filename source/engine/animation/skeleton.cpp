
/// \file example_class.cpp
/// \brief source file for class example.
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/animation/skeleton.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Animation
    {

        /// constructor detailed defintion,
        /// should be 2 lines
        Skeleton::Skeleton() :GameObject(Core::GameObjectType::Skeleton){}

        /// A detailed function description, it
        /// should be 2 lines at least.
        int Skeleton::GetVariable(int p1, float p2)
        {
            UNUSED_PARAMETER(p1);
            UNUSED_PARAMETER(p2);
            return 1;
        }

    }  // namespace Animation
}  // namespace vEngine