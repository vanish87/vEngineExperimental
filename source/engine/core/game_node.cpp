
/// \file game_node.cpp
/// \brief source file for Game Node
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/game_node.hpp>

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
            this->children_.push_back(component);
        }
        void GameNode::RemoveComponent(const GameNodeSharedPtr component) 
        {
            this->children_.remove(component);
        }
    }  // namespace Core

}  // namespace vEngine