/// \file light.cpp
/// \brief source file for light
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/light.hpp>
#include <vengine/core/game_object_factory.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {
        LightSharedPtr Light::Default()
        {
            return GameObjectFactory::Create<GameObjectType::Light, Light>();
        }

        /// constructor detailed defintion,
        /// should be 2 lines
        Light::Light(const GameObjectType type) : GameObject(type) {}

    }  // namespace Core

}  // namespace vEngine