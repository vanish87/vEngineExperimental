/// \file mesh_renderer.hpp
/// \brief Head file for Mesh Renderer
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_MESH_RENDERER_HPP
#define _VENGINE_CORE_MESH_RENDERER_HPP

#pragma once

#include <engine.hpp>
#include <VENGINE_API.h>
#include <vengine/core/renderer.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class VENGINE_API MeshRenderer : public Renderer<Mesh>
        {
            public:
                /// \brief brief constructor description.
                MeshRenderer();

                virtual void Render();
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_MESH_RENDERER_HPP */
