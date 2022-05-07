#ifndef _VENGINE_RENDERING_METAL_RENDERING_ENGINE_HPP
#define _VENGINE_RENDERING_METAL_RENDERING_ENGINE_HPP
#pragma once

#include <metal/metal.hpp>
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

                void OnBind(const FrameBufferSharedPtr frameBuffer) override
                {
                    UNUSED_PARAMETER(frameBuffer);
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

            private:
                void InitPipline();
                void DeinitPipline();
                void TriangleDraw();

            private:
        };

    }  // namespace Rendering
}  // namespace vEngine
#endif /* _VENGINE_RENDERING_METAL_RENDERING_ENGINE_HPP */
