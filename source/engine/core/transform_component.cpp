
/// \file mesh_component.cpp
/// \brief source file for Mesh Component
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/transform_component.hpp>
#include <vengine/core/transform_node.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {

        /// constructor detailed defintion,
        /// should be 2 lines
        void TransformComponent::OnUpdate()
        {
            auto current = this->Owner();
            auto parent = current->Parent().lock();
            if (parent != nullptr)
            {
                auto parent_transform = std::dynamic_pointer_cast<TransformNode>(parent);
                if (parent_transform != nullptr)
                {
                    this->GameObject()->UpdateLocalToWorld(parent_transform->Transform());
                }
                else
                {
                    this->GameObject()->UpdateLocalToWorld();
                    // PRINT_AND_BREAK("parent is not a transform node");
                }
            }
            else
            {
                PRINT_AND_BREAK("parent is null");
            }
        }
    }  // namespace Core

}  // namespace vEngine