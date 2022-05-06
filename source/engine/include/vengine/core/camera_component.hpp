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

#include <VENGINE_API.h>
#include <vengine/core/component.hpp>
#include <vengine/core/camera.hpp>
#include <vengine/rendering/frame_buffer.hpp>

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
                /// \brief brief constructor description.
                CameraComponent();

                void Update(const GameNodeSharedPtr parent) override
                {
                    auto cam = this->game_object_;
                    cam->target->UpdateGPU(this->Transform(), cam->ProjectionMatrix());
                }

                float4x4 ViewMatrix()
                {
                    return this->Transform();
                }
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_CAMERA_COMPONENT_HPP */
