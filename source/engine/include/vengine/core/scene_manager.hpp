/// \file scene_manager.hpp
/// \brief Head file for Scene Manager
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_SCENE_MANAGER_HPP
#define _VENGINE_CORE_SCENE_MANAGER_HPP

#pragma once

#include <queue>
#include <VENGINE_API.hpp>

#include <vengine/core/iruntime_module.hpp>
// #include <vengine/core/renderer.hpp>
#include <vengine/core/game_node.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class VENGINE_API SceneManager : public IRuntimeModule
        {
                SINGLETON_CLASS(SceneManager)
            public:
                /// \brief brief constructor description.
            public:
                void Init() override;
                void Deinit() override;

                /// \brief traverse all camera and render them
                void Update() override;

                /// \brief only render all objects
                void Flush();

                void BeginScene();



                SceneSharedPtr scene_;


        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_SCENE_MANAGER_HPP */
