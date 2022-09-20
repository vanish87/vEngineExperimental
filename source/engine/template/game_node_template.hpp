/// \file game_node_template.hpp
/// \brief Head file for template node
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _ENGINE_TEMPLATE_GAME_NODE_TEMPLATE_HPP
#define _ENGINE_TEMPLATE_GAME_NODE_TEMPLATE_HPP

#pragma once

#include <engine.hpp>
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
        class GameNodeTemplate : public GameNode
        {
            public:
                /// \brief brief constructor description.
                GameNodeTemplate();
                virtual ~GameNodeTemplate();

            public:
                /// \brief A brief function description.
                ///
                /// \param p1 Description for p1.
                /// \param p2 Description for p2.
                /// \return Description for return value.
                int GetVariable(int p1, float p2);
        };
    }  // namespace Core

}  // namespace vEngine

#endif /* _ENGINE_TEMPLATE_GAME_NODE_TEMPLATE_HPP */
