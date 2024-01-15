/// \file camera.hpp
/// \brief Head file for Camera
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_UI_UI_HPP
#define _VENGINE_UI_UI_HPP


#pragma once

#include <engine.hpp>
#include <vengine/core/game_object.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace UI
    {
        /// \brief A brief class description.
        ///
        /// Init IMGUI etc.
        /// may be attached with camera component to render ui for that camera
        class VENGINE_API UI : public Core::GameObject
        {
            public:
                // constexpr static auto properties()
                // {
                //     return std::tuple_cat(
                //         GameObject::properties(),
                //         std::make_tuple(
                //             property("fovy", &Camera::fovy_),
                //             property("aspect", &Camera::aspect_),
                //             property("zn", &Camera::zn_),
                //             property("zf", &Camera::zf_),
                //             property("project_matrix", &Camera::proj_matrix_),
                //             property("view_port", &Camera::view_port_)
                //         )
                //     );
                // }
                static UISharedPtr Default();
            public:
                /// \brief brief constructor description.
                UI();

            private:

        };
    }  // namespace Core
}  // namespace vEngine



#endif /* _VENGINE_UI_UI_HPP */
