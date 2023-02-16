/// \file renderer.hpp
/// \brief Head file for Renderer
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_RENDERING_RENDERER_HPP
#define _VENGINE_RENDERING_RENDERER_HPP

#pragma once

#include <engine.hpp>
#include <vengine/core/game_object.hpp>
#include <vengine/rendering/irenderer.hpp>

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
        class VENGINE_API Renderer : public Core::GameObject, public IRenderer
        {
            public:
                constexpr static auto properties()
                {
                    return std::tuple_cat(GameObject::properties(), std::make_tuple(property("material", &Renderer::material_)));
                };

            public:
                /// \brief brief constructor description.
                Renderer(){}
                bool UpdateRenderable()
                {
                    return false;
                }
                void Render()
                {
                    // pepare gpu dat from renderable_
                    // Get render engine
                    // render with gpu data
                    // re.Render(vertice info, this->material etc)
                }

                std::shared_ptr<T> renderable_;
                // gpu buffer etc.
                MaterialSharedPtr material_;
        };
    }  // namespace Rendering
}  // namespace vEngine

#endif /* _VENGINE_RENDERING_RENDERER_HPP */
