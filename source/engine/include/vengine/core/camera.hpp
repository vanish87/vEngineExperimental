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

#include <vengine/core/game_object.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class Camera : public GameObject
        {
            public:
                /// \brief brief constructor description.
                Camera();

                // aspect
                // fov
                // etc.
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_CAMERA_HPP */
