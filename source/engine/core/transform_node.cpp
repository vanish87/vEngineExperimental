
/// \file transform_node.cpp
/// \brief source file for Transform Node
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <engine.hpp>
#include <vengine/core/transform_node.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {
        void TransformNode::AttachComponent(const GameNodeSharedPtr component)
        {
            GameNode::AttachComponent(component);
            auto t = std::dynamic_pointer_cast<TransformComponent>(component);
            if (t != nullptr) this->transform_ = t;
        }
    }  // namespace Core
}  // namespace vEngine