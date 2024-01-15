/// \file camera.cpp
/// \brief source file for Camera
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/ui/ui.hpp>
#include <vengine/core/game_object_factory.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace UI
    {
        using namespace vEngine::Core;

        UISharedPtr UI::Default()
        {
            return GameObjectFactory::Create<GameObjectType::UI, UI>();
        }

        /// constructor detailed defintion,
        /// should be 2 lines
        UI::UI() 
        {
        }
    }  // namespace Core

}  // namespace vEngine