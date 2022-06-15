
/// \file mesh_component.cpp
/// \brief source file for Mesh Component
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/transform_component.hpp>

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
            if (parent != nullptr && parent->HasComponent<TransformComponent>())
            {
                auto t = parent->FirstOf<TransformComponent>();
                // PRINT("Node " << this->Owner()->name_ << "Update with " << parent->name_);
                this->GO()->UpdateLocalToWorld(t->GO());
            }
            else
            {
                // PRINT_AND_BREAK("parent is null");
                this->GO()->UpdateLocalToWorld();
            }
        }
    }  // namespace Core

}  // namespace vEngine