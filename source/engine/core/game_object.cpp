
/// \file game_object.cpp
/// \brief source file for Game Object
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/game_object.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {

        // GameObject::GameObject(const GameObject&& other)
        // {
        //     UNUSED_PARAMETER(other);
        //     NOT_IMPL_ASSERT;
        // }
        // GameObject::GameObject(const GameObject& other)
        // {
        //     UNUSED_PARAMETER(other);
        //     NOT_IMPL_ASSERT;
        // }
        /// constructor detailed defintion,
        /// should be 2 lines
        GameObject::GameObject(const GameObjectType type)
        {
            this->description_.type = type;
        }
        GameObject::~GameObject() {}
    }  // namespace Core

}  // namespace vEngine