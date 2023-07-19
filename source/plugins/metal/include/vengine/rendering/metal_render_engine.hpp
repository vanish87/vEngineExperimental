#ifndef _VENGINE_RENDERING_METAL_RENDER_ENGINE_HPP
#define _VENGINE_RENDERING_METAL_RENDER_ENGINE_HPP
#pragma once

#include <Metal/Metal.hpp>
#include <MetalKit/MTKView.hpp>
#include <UIKit/UIKit.hpp>
#include <vengine/rendering/render_engine.hpp>
#include <vengine/rendering/metal_mtk_view_delegate.hpp>
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

                // PipelineStateSharedPtr OnRegister(const PipelineStateDescriptor& pipeline_desc) override
                // {
                //     UNUSED_PARAMETER(pipeline_desc);
                //     return nullptr;
                // }
                void Render(const GraphicsBufferSharedPtr vertice, const GraphicsBufferSharedPtr indice) override
                {
                    UNUSED_PARAMETER(vertice);
                    UNUSED_PARAMETER(indice);
                }
                // TextureSharedPtr Create(const TextureDescriptor& desc) override
                // {
                //     UNUSED_PARAMETER(desc);
                //     return nullptr;
                // }
                // FrameBufferSharedPtr Create(const FrameBufferDescriptor& desc) override
                // {
                //     UNUSED_PARAMETER(desc);
                //     return nullptr;
                // }
                // GraphicsBufferSharedPtr Create(const GraphicsBufferDescriptor& desc) override
                // {
                //     UNUSED_PARAMETER(desc);
                //     return nullptr;
                // }
                void Clear(const FrameBufferSharedPtr frame_buffer, const Core::color color = Core::float4(0.0f, 0.2f, 0.4f, 1.0f)) override
                {
                    UNUSED_PARAMETER(frame_buffer);
                    UNUSED_PARAMETER(color);

                }

            private:
                void InitPipeline();
                void DeinitPipeline();
                void TriangleDraw();

            private:
                // MTL::Device device_;
                UI::ViewController* ui_view_controller_;
                MTL::Device* mtl_device_;
                MetalMTKViewDelegate* mtk_view_delegate_ = nullptr;
                MTK::View* mtk_view_;

                MTL::CommandQueue* command_queue_;
                MTL::RenderPipelineState* current_pipeline_state_;
                MTL::Buffer* vertex_buffer_;
                MTL::Buffer* color_buffer_;
        };

    }  // namespace Rendering
}  // namespace vEngine
#endif /* _VENGINE_RENDERING_METAL_RENDER_ENGINE_HPP */
