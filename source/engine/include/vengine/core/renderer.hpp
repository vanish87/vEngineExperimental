
/// \file renderer.hpp
/// \brief Head file for Renderer
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_RENDERER_HPP
#define _VENGINE_CORE_RENDERER_HPP

#pragma once

#include <engine.hpp>

#include <vengine/core/game_object.hpp>
#include <vengine/core/irenderer.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        template <typename T>
        class VENGINE_API Renderer : public GameObject, public IRenderer
        {
            public:
                constexpr static auto properties()
                {
                    return std::tuple_cat(
                        GameObject::properties(),
                        std::make_tuple(
                            property("material", &Renderer::material_)
                        )
                    );
                };
            public:
                /// \brief brief constructor description.
                Renderer()
                {

                };
                
                virtual bool UpdateRenderable()
                {
                    return false;
                }

                virtual void Render()
                {
                    // pepare gpu dat from renderable_
                    // Get render engine
                    // render with gpu data
                    // re.Render(vertice info, this->material etc)
                }

                std::shared_ptr<T> renderable_;
                // gpu buffer etc.
                Rendering::MaterialSharedPtr material_;
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_RENDERER_HPP */
