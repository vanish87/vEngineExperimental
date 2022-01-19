#ifndef _EMPTY_INCLUDE_EMPTY_RENDER_ENGINE_HPP
#define _EMPTY_INCLUDE_EMPTY_RENDER_ENGINE_HPP

#pragma once

#include <vengine/rendering/render_engine.hpp>

namespace vEngine
{
    namespace Rendering
    {
        class EmptyRenderEngine : public RenderEngine
        {
            public:
                EmptyRenderEngine()
                {
                    PRINT("Create Empty");
                }
                ~EmptyRenderEngine()
                {
                    PRINT("Destructor Empty");
                }
                void TestFunc();
                void Render() override;
                void CreateRenderWindow(void* hwnd) override;
                void PrintInfo() override;
        };
    }  // namespace Rendering
}  // namespace vEngine

#endif /* _EMPTY_INCLUDE_EMPTY_RENDER_ENGINE_HPP */
