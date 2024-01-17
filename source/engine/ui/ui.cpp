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
#include <external/imgui/imgui.h>

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
                // Setup Dear ImGui context
                IMGUI_CHECKVERSION();
                ImGui::CreateContext();
                ImGuiIO& io = ImGui::GetIO();
                io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
                io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls
                // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;      // IF using Docking Branch
        }
    }  // namespace Core

}  // namespace vEngine