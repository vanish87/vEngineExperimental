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

#include <cstring>
#include <vengine/core/component.hpp>
#include <vengine/rendering/mesh_renderer.hpp>
#include <vengine/core/mesh_component.hpp>
#include <vengine/core/transform_component.hpp>
#include <vengine/rendering/graphics_buffer.hpp>

#include <vengine/core/context.hpp>
#include <vengine/rendering/render_engine.hpp>
#include <vengine/rendering/shared/data_cbuffer.hpp>
#include <vengine/animation/bone_component.hpp>

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
