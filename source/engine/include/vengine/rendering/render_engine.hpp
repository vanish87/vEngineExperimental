#ifndef _VENGINE_RENDERING_RENDER_ENGINE_HPP
#define _VENGINE_RENDERING_RENDER_ENGINE_HPP

#pragma once
#include <map>

#include <engine.hpp>
#include <vengine/rendering/data_struct.hpp>
#include <vengine/rendering/data_format.hpp>
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

                virtual void OnBeginFrame()
                {
                    // const color color = color(0, 51, 102, 255);
                    // update per frame cbuffer
                    this->Clear(this->current_frame_buffer_, color(0, 51, 102, 255));
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

                // virtual PipelineStateSharedPtr Create(const PipelineStateDescriptor& pipeline_desc) = 0;
                // virtual TextureSharedPtr Create(const TextureDescriptor& desc) = 0;
                // virtual FrameBufferSharedPtr Create(const FrameBufferDescriptor& desc) = 0;
                // virtual GraphicsBufferSharedPtr Create(const GraphicsBufferDescriptor& desc) = 0;

                // virtual void Clear(const FrameBufferSharedPtr frame_buffer, const color color = color(0, 51, 102, 255)) = 0;
                virtual void Clear(const FrameBufferSharedPtr frame_buffer, const color color) = 0;

                FrameBufferSharedPtr current_frame_buffer_;
                FrameBufferSharedPtr back_buffer_;

                // std::map<std::string, PipelineStateSharedPtr> current_pipline_states;
                // PipelineStateSharedPtr current_pipline_state_;
        };
    }  // namespace Rendering
}  // namespace vEngine

// extern "C"
// {
//     VENGINE_API void CreateRenderEngine(std::unique_ptr<vEngine::Rendering::RenderEngine>& ptr);
//     VENGINE_API void DestoryRenderEngine(std::unique_ptr<vEngine::Rendering::RenderEngine>& ptr);
// }
#ifdef VENGINE_STATIC_LINK
// extern "C"
// {
    void CreateRenderEngine(std::unique_ptr<vEngine::Rendering::RenderEngine>& ptr);
    void DestoryRenderEngine(std::unique_ptr<vEngine::Rendering::RenderEngine>& ptr);
// }
#endif
#endif /* _VENGINE_RENDERING_RENDER_ENGINE_HPP */
