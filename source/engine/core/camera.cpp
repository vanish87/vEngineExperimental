/// \file camera.cpp
/// \brief source file for Camera
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/camera.hpp>
#include <vengine/core/game_object_factory.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {
        CameraSharedPtr Camera::Default()
        {
            return GameObjectFactory::Create<GameObjectType::Camera, Camera>();
        }

        /// constructor detailed defintion,
        /// should be 2 lines
        Camera::Camera(const GameObjectType type) : GameObject(type), fovy_{Math::PI / 4}, aspect_{1}, zn_{0.01f}, zf_{1000}
        {
            this->proj_matrix_ = Math::PerspectiveFovLH(this->fovy_, this->aspect_, this->zn_, this->zf_);
        }
    }  // namespace Core

}  // namespace vEngine