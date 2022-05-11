/// \file scene.hpp
/// \brief Head file for Scene Node
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_SCENE_HPP
#define _VENGINE_CORE_SCENE_HPP

#pragma once

#include <engine.hpp>
#include <vengine/core/game_node.hpp>
#include <vengine/core/iresource.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class Scene : public GameNode, public IResource
        {
            public:
                /// \brief brief constructor description.
                Scene();

                bool Load() override;

                /// class variable description
                // int public_variable_;

            public:
                /// \brief A brief function description.
                ///
                /// \param p1 Description for p1.
                /// \param p2 Description for p2.
                /// \return Description for return value.
                // int GetVariable(int p1, float p2);

            private:
        };

    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_SCENE_HPP */
