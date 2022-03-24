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

#include <VENGINE_API.h>

#include <engine.hpp>
#include <functional>
#include <list>
#include <vengine/core/matrix.hpp>
#include <vengine/core/uuid.hpp>

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
        class VENGINE_API GameNode
        {
            public:
                /// \brief brief constructor description.
                GameNode();
                virtual ~GameNode();

                void AddComponent(const GameNodeSharedPtr component);
                void RemoveComponent(const GameNodeSharedPtr component);

                template <typename T>
                void ForEach(std::function<void(T*)> const& iter)
                {
                    for (auto c : this->children_)
                    {
                        auto go = dynamic_cast<T*>(c.get());
                        if (go != nullptr)
                        {
                            iter(go);
                        }
                    }
                }

            private:
                // transform
                float4x4 transform_;
                // children also used as list of gameobject/components
                std::list<GameNodeSharedPtr> children_;
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_GAME_NODE_HPP */
