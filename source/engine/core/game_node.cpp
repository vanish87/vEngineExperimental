
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
// #include <vengine/core/transform_component.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {

        /// constructor detailed defintion,
        /// should be 2 lines
        GameNode::GameNode() 
        {
            // this->description_.name = "Raw GameNode";
        }
        GameNode::~GameNode() {}

        // TransformSharedPtr GameNode::Transform()
        // {
        //     return this->transform_->game_object_;
        // }

        void GameNode::AttachComponent(const GameNodeSharedPtr component)
        {
            auto com = std::dynamic_pointer_cast<IComponent>(component);
            CHECK_ASSERT_NOT_NULL(com);

            if (com != nullptr)
            {
                this->AddChild(component);
            }
        }
        void GameNode::DetachComponent(const GameNodeSharedPtr component)
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
            // auto ptr = GameNode::shared_from_this();
            if (game_node->parent_.expired() == false) PRINT_AND_BREAK("game_node is already a child");

            auto com = std::dynamic_pointer_cast<IComponent>(shared_from_this());
            if (com != nullptr) PRINT_AND_BREAK("component usually does not have a child");

            game_node->parent_ = weak_from_this();
            this->children_.push_back(game_node);

            // auto transform = std::dynamic_pointer_cast<TransformComponent>(game_node);
            // if(transform != nullptr) this->transform_ = transform;
        }
        void GameNode::RemoveChild(const GameNodeSharedPtr game_node)
        {
            game_node->parent_.reset();
            this->children_.remove(game_node);
        }
    }  // namespace Core

}  // namespace vEngine