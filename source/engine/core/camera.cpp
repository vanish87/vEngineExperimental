/// \file camera.cpp
/// \brief source file for Camera
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/camera.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {

        /// constructor detailed defintion,
        /// should be 2 lines
        Camera::Camera() : GameObject(GameObjectType::Camera), fovy_{Math::PI / 4}, aspect_{1}, zn_{0.01f}, zf_{1000}
        {
            this->proj_matrix_ = Math::PerspectiveFovLH(this->fovy_, this->aspect_, this->zn_, this->zf_);
        }
    }  // namespace Core

}  // namespace vEngine