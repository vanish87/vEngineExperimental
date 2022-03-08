/// \file mesh_renderer_component.hpp
/// \brief Head file for Mesh Renderer Component
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_MESH_RENDERER_COMPONENT_HPP
#define _VENGINE_CORE_MESH_RENDERER_COMPONENT_HPP

#include <vengine/core/component.hpp>
#include <vengine/core/mesh_renderer.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Rendering
    {
        using namespace vEngine::Core;
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class MeshRendererComponent : public Component<MeshRenderer>
        {
            public:
                /// \brief brief constructor description.
                MeshRendererComponent();
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_MESH_RENDERER_COMPONENT_HPP */