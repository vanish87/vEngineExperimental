#ifndef _VENGINE_RENDERING_RENDER_ENGINE_HPP
#define _VENGINE_RENDERING_RENDER_ENGINE_HPP

#pragma once

#include <map>
#include <VENGINE_API.h>

#include <engine.hpp>
#include <vengine/core/iruntime_module.hpp>

namespace vEngine
{
    namespace Rendering
    {
        class VENGINE_API RenderEngine : public vEngine::Core::IRuntimeModule
        {
            public:
                virtual ~RenderEngine(){};

                virtual void PrintInfo() = 0;

                virtual void Init() = 0;
                virtual void Deinit() = 0;
                virtual void Update() = 0;

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

                virtual void OnBeginFrame(){
                    //update per frame cbuffer
                }; 

                virtual void BeginRender(){};
                virtual void Render(const GraphicsBufferSharedPtr vertice, const GraphicsBufferSharedPtr indice) = 0;
                virtual void EndRender(){};

                virtual void Dispatch(){};

                // virutal void SetupFrameTextureToRender
                //GPU Resource management
                // virtual void 

                virtual TextureSharedPtr Create(const TextureDescriptor& desc) = 0;
                virtual FrameBufferSharedPtr Create(const FrameBufferDescriptor& desc) = 0;
                virtual GraphicsBufferSharedPtr Create(const GraphicsBufferDescriptor& desc) = 0;


                FrameBufferSharedPtr current_frame_buffer_;
                FrameBufferSharedPtr back_buffer_;

                std::map<std::string, PipelineStateSharedPtr> current_pipline_states;
                
        };
    }  // namespace Rendering
}  // namespace vEngine

extern "C" {
    VENGINE_API void CreateRenderEngine(std::unique_ptr<vEngine::Rendering::RenderEngine>& ptr);
    VENGINE_API void DestoryRenderEngine(std::unique_ptr<vEngine::Rendering::RenderEngine>& ptr);
}
#endif /* _VENGINE_RENDERING_RENDER_ENGINE_HPP */
