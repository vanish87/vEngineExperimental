#ifndef _VENGINE_RENDERING_RENDER_ENGINE_HPP
#define _VENGINE_RENDERING_RENDER_ENGINE_HPP

#pragma once

#include <VENGINE_API.h>

#include <engine.hpp>

namespace vEngine
{
    namespace Rendering
    {
        class VENGINE_API RenderEngine
        {
            public:
                virtual void CreateRenderWindow() = 0;
                virtual void Render() = 0;

            private:
                void CreateInternal();
        };
    }  // namespace Rendering
}  // namespace vEngine

#endif /* _VENGINE_RENDERING_RENDER_ENGINE_HPP */
