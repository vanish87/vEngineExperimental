/// \file camera.hpp
/// \brief Head file for Camera
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_CAMERA_HPP
#define _VENGINE_CORE_CAMERA_HPP

#pragma once

#include <engine.hpp>
#include <vengine/core/game_object.hpp>
#include <vengine/core/matrix.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class VENGINE_API Camera : public GameObject
        {
            public:
                constexpr static auto properties()
                {
                    return std::tuple_cat(
                        GameObject::properties(),
                        std::make_tuple(
                            property("fovy", &Camera::fovy_),
                            property("aspect", &Camera::aspect_),
                            property("zn", &Camera::zn_),
                            property("zf", &Camera::zf_),
                            property("project_matrix", &Camera::proj_matrix_),
                            property("view_port", &Camera::view_port_)
                        )
                    );
                }
                static CameraSharedPtr Default();
            public:
                /// \brief brief constructor description.
                Camera();

                Rendering::FrameBufferSharedPtr target;


                const float4x4 ProjectionMatrix() const
                {
                    return this->proj_matrix_;
                }

            private:
                float fovy_;
                float aspect_;
                float zn_;
                float zf_;
                float4x4 proj_matrix_;
                // aspect
                // fov
                // etc.

                int4 view_port_;

        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_CAMERA_HPP */
