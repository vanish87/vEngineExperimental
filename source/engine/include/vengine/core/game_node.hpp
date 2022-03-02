/// \file game_node.hpp
/// \brief Head file for Game Node
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_GAME_NODE_HPP
#define _VENGINE_CORE_GAME_NODE_HPP

#pragma once

#include <engine.hpp>
#include <list>
#include <vengine/core/matrix.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        using namespace vEngine::Math;
        /// \brief Game Node is basic game scene object
        ///
        /// It contains a tranfrom and a list of children nodes
        /// and contructs a tree struture that presents the game scene
        /// the child of GameNode could be a normal game node or
        /// a component that referenced to other game object class
        class GameNode
        {
            public:
                /// \brief brief constructor description.
                GameNode();

            private:
                // transform
                float4x4 transform_;
                // children also used as list of gameobject/components
                std::list<GameNodeSharedPtr> children_;
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_GAME_NODE_HPP */
