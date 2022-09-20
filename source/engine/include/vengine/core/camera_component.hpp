/// \file camera_component.hpp
/// \brief Head file for Camera Component
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_CAMERA_COMPONENT_HPP
#define _VENGINE_CORE_CAMERA_COMPONENT_HPP

#pragma once

#include <VENGINE_API.hpp>
#include <engine.hpp>
#include <vengine/core/camera.hpp>
#include <vengine/core/component.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class VENGINE_API CameraComponent : public Component<Camera>
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
                CameraComponent(const GameObjectType type = GameObjectType::CameraComponent);

                void OnBeginCamera();

                Rendering::GraphicsBufferSharedPtr camera_constant_buffer_;
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_CAMERA_COMPONENT_HPP */
