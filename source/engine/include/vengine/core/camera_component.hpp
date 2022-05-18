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
#include <VENGINE_API.hpp>
#include <vengine/core/component.hpp>
#include <vengine/core/transform_node.hpp>
#include <vengine/core/transform_component.hpp>
#include <vengine/core/camera.hpp>
#include <vengine/rendering/graphics_buffer.hpp>

#include <vengine/core/context.hpp>
#include <vengine/rendering/render_engine.hpp>

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
                    cb.camera_pos = float4(0, 0, 100, 1);

                    auto trans = std::dynamic_pointer_cast<TransformNode>(this->Owner());
                    cb.view_matrix = trans->transform_->game_object_->LocalToWorldTransform();
                    // Math::Translate(cb.view_matrix, 0, 0, 100);
                    // cb.view_matrix = Math::Transpose(cb.view_matrix);
                    cb.proj_matrix = cam->ProjectionMatrix();
                    // cb.proj_matrix = Math::Transpose(cb.proj_matrix);
                    auto data = this->camera_constant_buffer_->Map();
                    std::memcpy(data.data, &cb, sizeof(vEngineCameraConstantBuffer));
                    // std::copy(&cb, &cb + sizeof(vEngineCameraConstantBuffer), data.data);
                    this->camera_constant_buffer_->Unmap();

                    Context::GetInstance().GetRenderEngine().OnBind(this->camera_constant_buffer_);
                }



                GraphicsBufferSharedPtr camera_constant_buffer_;
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_CAMERA_COMPONENT_HPP */
