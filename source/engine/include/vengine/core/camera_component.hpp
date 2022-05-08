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

#include <cstring>
#include <VENGINE_API.h>
#include <vengine/core/component.hpp>
#include <vengine/core/camera.hpp>
#include <vengine/rendering/graphics_buffer.hpp>

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

                void OnBeginCamera()
                {
                    auto cam = this->game_object_;
                    vEngineCameraConstantBuffer cb;
                    cb.view_matrix = this->LocalToWorldTransform();
                    cb.proj_matrix = cam->ProjectionMatrix();
                    auto data = this->camera_constant_buffer_->Map();
                    std::memcpy(data.data, &cb, sizeof(vEngineCameraConstantBuffer));
                    // std::copy(&cb, &cb + sizeof(vEngineCameraConstantBuffer), data.data);
                    this->camera_constant_buffer_->Unmap();
                }

                void Update(const GameNodeSharedPtr parent) override
                {
                    UNUSED_PARAMETER(parent);
                }


                GraphicsBufferSharedPtr camera_constant_buffer_;
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_CAMERA_COMPONENT_HPP */
