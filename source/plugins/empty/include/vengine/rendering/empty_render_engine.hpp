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
                FrameBufferSharedPtr Create(const FrameBufferDescriptor& desc)
                {
                    UNUSED_PARAMETER(desc);
                    return nullptr;
                }
                GraphicsBufferSharedPtr Create(const GraphicsBufferDescriptor& desc)
                {
                    UNUSED_PARAMETER(desc);
                    return nullptr;
                }
        };
    }  // namespace Rendering
}  // namespace vEngine

#endif /* _EMPTY_INCLUDE_EMPTY_RENDER_ENGINE_HPP */
