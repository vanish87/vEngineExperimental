#ifndef _VENGINE_RENDERING_METAL_RENDERING_ENGINE_HPP
#define _VENGINE_RENDERING_METAL_RENDERING_ENGINE_HPP
#pragma once

// #include <metal/metal.hpp>
#include <vengine/rendering/render_engine.hpp>
namespace vEngine
{
    namespace Rendering
    {
        class MetalRenderEngine : public RenderEngine
        {
            public:
                MetalRenderEngine()
                {
                    PRINT("Create Metal");
                }
                ~MetalRenderEngine()
                {
                    PRINT("Destructor Metal");
                }
                void Init() override;
                void Deinit() override;
                void Update() override;
                void PrintInfo() override;

            private:
                void InitPipline();
                void DeinitPipline();
                void TriangleDraw();

            private:
        };

    }  // namespace Rendering
}  // namespace vEngine
#endif /* _VENGINE_RENDERING_METAL_RENDERING_ENGINE_HPP */
