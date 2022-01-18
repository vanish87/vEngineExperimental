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
                virtual ~RenderEngine(){};

                virtual void CreateRenderWindow(void* hwnd) = 0;
                virtual void Render() = 0;

                virtual void PrintInfo() = 0;

            private:
                void CreateInternal();
        };
    }  // namespace Rendering
}  // namespace vEngine

extern "C" {
    VENGINE_API void CreateRenderEngine(std::unique_ptr<vEngine::Rendering::RenderEngine>& ptr);
    VENGINE_API void DestoryRenderEngine(std::unique_ptr<vEngine::Rendering::RenderEngine>& ptr);
}
#endif /* _VENGINE_RENDERING_RENDER_ENGINE_HPP */
