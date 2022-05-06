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
        Camera::Camera() : fovy_{1}, aspect_{1}, zn_{0.01f}, zf_{10}
        {
            this->proj_matrix_ = Math::PerspectiveFovLH(this->fovy_, this->aspect_, this->zn_, this->zf_);
        }
    }  // namespace Core

}  // namespace vEngine