/// \file transform.cpp
/// \brief source file for Transform
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/transform.hpp>
#include <vengine/core/game_object_factory.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {
        TransformSharedPtr Transform::Default()
        {
            return GameObjectFactory::Create<GameObjectType::Transform, Transform>();
        }
    }  // namespace Core
}  // namespace vEngine
