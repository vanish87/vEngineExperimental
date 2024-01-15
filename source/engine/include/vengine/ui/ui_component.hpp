/// \file camera_component.hpp
/// \brief Head file for Camera Component
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_UI_UI_COMPONENT_HPP
#define _VENGINE_UI_UI_COMPONENT_HPP

#pragma once

#include <engine.hpp>
#include <vengine/ui/ui.hpp>
#include <vengine/core/component.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace UI
    {
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class VENGINE_API UIComponent : public Core::Component<UI>
        {
            public:
                // constexpr static auto properties()
                // {
                //     return std::tuple_cat(
                //         Component::properties()
                //         // std::make_tuple(
                //         //     property("enabled", &Component::enabled_),
                //         //     property("game_object", &Component::game_object_)
                //         // )
                //     );
                // }
            public:
                /// \brief brief constructor description.
                UIComponent();

                // void OnBeginCamera();

                // Rendering::GraphicsBufferSharedPtr camera_constant_buffer_;
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_UI_UI_COMPONENT_HPP */
