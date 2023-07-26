/// \file mesh_renderer_component.hpp
/// \brief Head file for Mesh Renderer Component
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_RENDERING_MESH_RENDERER_COMPONENT_HPP
#define _VENGINE_RENDERING_MESH_RENDERER_COMPONENT_HPP

#include <vengine/rendering/mesh_renderer.hpp>
#include <vengine/core/component.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Rendering
    {
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class VENGINE_API MeshRendererComponent : public Core::Component<MeshRenderer>
        {
            public:
                /// \brief brief constructor description.
                MeshRendererComponent();

                void OnBeginRender();
                virtual void OnUpdate() override;
                //world matrix etc.
                GraphicsBufferSharedPtr mesh_constant_buffer_;
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_RENDERING_MESH_RENDERER_COMPONENT_HPP */
