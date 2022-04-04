
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
        GameNode::GameNode() {}
        GameNode::~GameNode() {}

        void GameNode::AddComponent(const GameNodeSharedPtr component)
        {
            auto com = dynamic_cast<IComponent*>(component.get());
            CHECK_ASSERT_NOT_NULL(com);
            if (com != nullptr)
            {
                this->AddChild(component);
            }
        }
        void GameNode::RemoveComponent(const GameNodeSharedPtr component)
        {
            auto com = dynamic_cast<IComponent*>(component.get());
            CHECK_ASSERT_NOT_NULL(com);
            if (com != nullptr)
            {
                this->RemoveChild(component);
            }
        }

        void GameNode::AddChild(const GameNodeSharedPtr game_node)
        {
            this->children_.push_back(game_node);
        }
        void GameNode::RemoveChild(const GameNodeSharedPtr game_node)
        {
            this->children_.remove(game_node);
        }
    }  // namespace Core

}  // namespace vEngine