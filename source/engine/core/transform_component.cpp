
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
            auto parent = std::dynamic_pointer_cast<TransformNode>(current->Parent().lock());
            if (parent != nullptr)
            {
                this->GameObject()->UpdateLocalToWorld(parent->Transform());
            }
            else
            {
                // PRINT_AND_BREAK("parent is null");
                this->GameObject()->UpdateLocalToWorld();
            }
        }
    }  // namespace Core

}  // namespace vEngine