/// \file renderer_component.hpp
/// \brief Head file for Renderer Component
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_RENDERING_RENDERER_COMPONENT_HPP
#define _VENGINE_RENDERING_RENDERER_COMPONENT_HPP

#pragma once

#include <engine.hpp>
#include <vengine/rendering/renderer.hpp>
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
        template <typename T>
        class VENGINE_API RendererComponent : public Core::Component<Renderer<T>>
        {
            public:
                /// \brief brief constructor description.
                RendererComponent(const Core::GameObjectType type = Core::GameObjectType::RendererComponent) : Core::Component(type){};
        };
    }  // namespace Rendering
}  // namespace vEngine

#endif /* _VENGINE_RENDERING_RENDERER_COMPONENT_HPP */
