/// \file mesh_component.hpp
/// \brief Head file for Mesh Component
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_MESH_COMPONENT_HPP
#define _VENGINE_CORE_MESH_COMPONENT_HPP

#include <engine.hpp>
#include <vengine/core/mesh.hpp>
#include <vengine/core/component.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class VENGINE_API MeshComponent : public Component<Mesh>
        {
            public:
                /// \brief brief constructor description.
                // MeshComponent();
                MeshComponent(const MeshSharedPtr mesh = Mesh::Default());
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_MESH_COMPONENT_HPP */
