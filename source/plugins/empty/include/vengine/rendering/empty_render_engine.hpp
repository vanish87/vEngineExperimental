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

                PipelineStateSharedPtr OnRegister(const PipelineStateDescriptor& pipeline_desc) override
                {
                    UNUSED_PARAMETER(pipeline_desc);
                    return nullptr;
                }
                void Render(const GraphicsBufferSharedPtr vertice, const GraphicsBufferSharedPtr indice) override
                {
                    UNUSED_PARAMETER(vertice);
                    UNUSED_PARAMETER(indice);
                }
                TextureSharedPtr Create(const TextureDescriptor& desc) override
                {
                    UNUSED_PARAMETER(desc);
                    return nullptr;
                }
                FrameBufferSharedPtr Create(const FrameBufferDescriptor& desc) override
                {
                    UNUSED_PARAMETER(desc);
                    return nullptr;
                }
                GraphicsBufferSharedPtr Create(const GraphicsBufferDescriptor& desc) override
                {
                    UNUSED_PARAMETER(desc);
                    return nullptr;
                }
                void Clear(const FrameBufferSharedPtr frame_buffer, const color color) override
                {
                    UNUSED_PARAMETER(frame_buffer);
                    UNUSED_PARAMETER(color);
                }
        };
    }  // namespace Rendering
}  // namespace vEngine

#endif /* _EMPTY_INCLUDE_EMPTY_RENDER_ENGINE_HPP */
