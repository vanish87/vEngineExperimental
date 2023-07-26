/// \file mesh_renderer.hpp
/// \brief Head file for Mesh Renderer
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_RENDERING_MESH_RENDERER_HPP
#define _VENGINE_RENDERING_MESH_RENDERER_HPP

#pragma once

#include <engine.hpp>
#include <vengine/core/mesh.hpp>
#include <vengine/rendering/renderer.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Rendering
    {
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class VENGINE_API MeshRenderer : public Renderer<Core::Mesh>
        {
            public:
                static MeshRendererSharedPtr Default();

            public:
                /// \brief brief constructor description.
                MeshRenderer();
                ~MeshRenderer();

                virtual void Render();
        };
    }  // namespace Rendering
}  // namespace vEngine

#endif /* _VENGINE_RENDERING_MESH_RENDERER_HPP */
