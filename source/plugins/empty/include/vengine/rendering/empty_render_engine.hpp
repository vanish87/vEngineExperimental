#ifndef _VENGINE_RENDERING_EMPTY_RENDER_ENGINE_HPP
#define _VENGINE_RENDERING_EMPTY_RENDER_ENGINE_HPP

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
                void Init() override;
                void Update() override;
                void Deinit() override;
                void PrintInfo() override;
                void OnBind(const FrameBufferSharedPtr frameBuffer) override
                {
                    UNUSED_PARAMETER(frameBuffer);
                }
                void OnBind(const PipelineStateSharedPtr pipeline_state) override
                {
                    UNUSED_PARAMETER(pipeline_state);
                }
                void OnBind(const GraphicsBufferSharedPtr graphics_buffer) override
                {
                    UNUSED_PARAMETER(graphics_buffer);
                }
                void OnBind(const TextureSharedPtr texture) override
                {
                    UNUSED_PARAMETER(texture);
                }

                void Render(const GraphicsBufferSharedPtr vertice, const GraphicsBufferSharedPtr indice) override
                {
                    UNUSED_PARAMETER(vertice);
                    UNUSED_PARAMETER(indice);
                }
                void Clear(const FrameBufferSharedPtr frame_buffer, const Core::color color) override
                {
                    UNUSED_PARAMETER(frame_buffer);
                    UNUSED_PARAMETER(color);
                }
        };
    }  // namespace Rendering
}  // namespace vEngine

#endif /* _VENGINE_RENDERING_EMPTY_RENDER_ENGINE_HPP */
