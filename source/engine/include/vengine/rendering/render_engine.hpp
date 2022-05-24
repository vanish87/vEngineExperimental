#ifndef _VENGINE_RENDERING_RENDER_ENGINE_HPP
#define _VENGINE_RENDERING_RENDER_ENGINE_HPP

#pragma once

#include <VENGINE_API.hpp>

#include <engine.hpp>
#include <map>
#include <vengine/core/iruntime_module.hpp>
#include <vengine/core/transform.hpp>

namespace vEngine
{
    namespace Rendering
    {
        using namespace Core;

        class VENGINE_API RenderEngine : public vEngine::Core::IRuntimeModule
        {
            public:
                virtual ~RenderEngine()
                {
                };

                virtual void PrintInfo() = 0;

                virtual void Init() = 0;
                virtual void Deinit()
                {
                    // this->current_pipline_state_ = nullptr;
                    this->current_frame_buffer_ = nullptr;
                }
                virtual void Update() = 0;

                virtual void Bind(const PipelineStateSharedPtr pipline_state)
                {
                    // this->current_pipline_state_ = pipline_state;
                    this->OnBind(pipline_state);
                }
                virtual void OnBind(const PipelineStateSharedPtr pipeline_state) = 0;

                virtual void Bind(const GraphicsBufferSharedPtr graphics_buffer)
                {
                    this->OnBind(graphics_buffer);
                }
                virtual void OnBind(const GraphicsBufferSharedPtr graphics_buffer) = 0;
                
                virtual void Bind(const TextureSharedPtr texture)
                {
                    this->OnBind(texture);
                }
                virtual void OnBind(const TextureSharedPtr texture) = 0;

                virtual void Bind(const FrameBufferSharedPtr frameBuffer)
                {
                    this->current_frame_buffer_ = frameBuffer;
                    this->OnBind(frameBuffer);
                }
                virtual void OnBind(const FrameBufferSharedPtr frameBuffer) = 0;

                virtual PipelineStateSharedPtr Register(const PipelineStateDescriptor& pipeline_desc)
                {
                    // this->current_pipline_states = frameBuffer;
                    return this->OnRegister(pipeline_desc);
                }
                virtual PipelineStateSharedPtr OnRegister(const PipelineStateDescriptor& pipeline_desc) = 0;

                virtual void OnBeginFrame()
                {
                    // update per frame cbuffer
                    this->Clear(this->current_frame_buffer_);
                };
                virtual void OnEndFrame()
                {

                };

                virtual void BeginRender(){
                    // per object cbuffer
                };
                virtual void Render(const GraphicsBufferSharedPtr vertice, const GraphicsBufferSharedPtr indice) = 0;
                virtual void EndRender(){};

                virtual void Dispatch(){};

                // virutal void SetupFrameTextureToRender
                // GPU Resource management
                // virtual void

                virtual TextureSharedPtr Create(const TextureDescriptor& desc) = 0;
                virtual FrameBufferSharedPtr Create(const FrameBufferDescriptor& desc) = 0;
                virtual GraphicsBufferSharedPtr Create(const GraphicsBufferDescriptor& desc) = 0;

                virtual void Clear(const FrameBufferSharedPtr frame_buffer, const color color = float4(0.0f, 0.2f, 0.4f, 1.0f)) = 0;

                FrameBufferSharedPtr current_frame_buffer_;
                FrameBufferSharedPtr back_buffer_;

                // std::map<std::string, PipelineStateSharedPtr> current_pipline_states;
                // PipelineStateSharedPtr current_pipline_state_;
        };
    }  // namespace Rendering
}  // namespace vEngine

extern "C"
{
    VENGINE_API void CreateRenderEngine(std::unique_ptr<vEngine::Rendering::RenderEngine>& ptr);
    VENGINE_API void DestoryRenderEngine(std::unique_ptr<vEngine::Rendering::RenderEngine>& ptr);
}
#endif /* _VENGINE_RENDERING_RENDER_ENGINE_HPP */
