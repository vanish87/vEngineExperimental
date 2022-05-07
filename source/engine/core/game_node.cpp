
/// \file game_node.cpp
/// \brief source file for Game Node
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/game_node.hpp>
#include <vengine/core/icomponent.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {

        /// constructor detailed defintion,
        /// should be 2 lines
        GameNode::GameNode() : parent_{nullptr} {}
        GameNode::~GameNode() {}

        void GameNode::AddComponent(const GameNodeSharedPtr component)
        {
            auto com = std::dynamic_pointer_cast<IComponent>(component);
            CHECK_ASSERT_NOT_NULL(com);
            if (com != nullptr)
            {
                this->AddChild(component);
            }
        }
        void GameNode::RemoveComponent(const GameNodeSharedPtr component)
        {
            auto com = std::dynamic_pointer_cast<IComponent>(component);
            CHECK_ASSERT_NOT_NULL(com);
            if (com != nullptr)
            {
                this->RemoveChild(component);
            }
        }

        void GameNode::AddChild(const GameNodeSharedPtr game_node)
        {
            game_node->parent_ = shared_from_this();
            this->children_.push_back(game_node);
        }
        void GameNode::RemoveChild(const GameNodeSharedPtr game_node)
        {
            game_node->parent_ = nullptr;
            this->children_.remove(game_node);
        }
    }  // namespace Core

}  // namespace vEngine