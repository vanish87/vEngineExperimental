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
        using namespace Math;
        using namespace Rendering;
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class Camera : public GameObject
        {
            public:
                /// \brief brief constructor description.
                Camera();

                FrameBufferSharedPtr target;

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
