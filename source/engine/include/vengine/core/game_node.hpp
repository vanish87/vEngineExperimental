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
#include <vengine/core/transform.hpp>

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
        class VENGINE_API GameNode : public std::enable_shared_from_this<GameNode>
        {
            public:
                /// \brief brief constructor description.
                GameNode();
                virtual ~GameNode();

                void AddChild(const GameNodeSharedPtr game_node);
                void RemoveChild(const GameNodeSharedPtr game_node);
                
                void AddComponent(const GameNodeSharedPtr component);
                void RemoveComponent(const GameNodeSharedPtr component);

                float4x4 LocalTransform()
                {
                    return this->transform_.local_;
                }
                float4x4 LocalToWorldTransform()
                {
                    return this->transform_.local_to_world_;
                }
                void SetScale(float3 scale)
                {
                    Math::Scale(this->transform_.local_, scale);
                }

                void UpdateLocal(GameNodeSharedPtr parent)
                {
                    this->transform_.local_to_world_ = this->transform_.local_ * parent->LocalToWorldTransform();
                }

                template <typename T>
                std::shared_ptr<T> FirstOf()
                {
                    for (auto c : this->children_)
                    {
                        auto go = std::dynamic_pointer_cast<T>(c);
                        if (go != nullptr)
                        {
                            return go;
                        }
                    }
                    return nullptr;
                }
                template <typename T>
                void ForEachChild(std::function<void(std::shared_ptr<T>)> const& iter)
                {
                    for (auto c : this->children_)
                    {
                        auto go = std::dynamic_pointer_cast<T>(c);
                        if (go != nullptr)
                        {
                            iter(go);
                        }
                    }
                }
                template <typename T>
                void Traverse(std::function<bool(std::shared_ptr<T>)> const& func)
                {
                    auto gn = std::dynamic_pointer_cast<T>(shared_from_this());
                    if (gn == nullptr ? true : func(gn))
                    {
                        for (const auto& c : this->children_)
                        {
                            c->Traverse(func);
                        }
                    }
                }
                template <typename T>
                void Traverse(std::function<bool(std::shared_ptr<T>, const GameNodeSharedPtr)> const& func)
                {
                    for (const auto& c : this->children_)
                    {
                        auto gn = std::dynamic_pointer_cast<T>(c);
                        if (gn == nullptr ? true : func(gn, shared_from_this()))
                        {
                            c->Traverse(func);
                        }
                    }
                }
                // template <typename T>
                // void ForEachChild(std::function<void(T*)> const& iter)
                // {
                //     for (auto c : this->children_)
                //     {
                //         auto go = dynamic_cast<T*>(c.get());
                //         if (go != nullptr)
                //         {
                //             iter(go);
                //         }
                //     }
                // }
                // template <typename T>
                // void Traverse(std::function<bool(T*)> const& func)
                // {
                //     if (func(this))
                //     {
                //         for (const auto& c : this->children_)
                //         {
                //             c->Traverse(func);
                //         }
                //     }
                // }

            private:
                // transform
                Transform transform_;
                // children also used as list of gameobject/components
                std::list<GameNodeSharedPtr> children_;
                GameNodeSharedPtr parent_;
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_GAME_NODE_HPP */
