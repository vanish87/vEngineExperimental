#ifndef _VENGINE_RENDERING_RENDER_ENGINE_HPP
#define _VENGINE_RENDERING_RENDER_ENGINE_HPP

#pragma once

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

                virtual void BeginRender(){};
                virtual void Render(GraphicsBufferSharedPtr vertex)
                {
                    UNUSED_PARAMETER(vertex);
                    //very basic rendering of sth.
                    //IASetBuffer
                    //IASetTopology
                    //DrawIndexed

                };
                virtual void EndRender(){};

                virtual void Dispatch(){};

                // virutal void SetupFrameTextureToRender
                //GPU Resource management
                // virtual void 

                virtual TextureSharedPtr Create(const TextureDescriptor& desc) = 0;
                virtual FrameBufferSharedPtr Create(const FrameBufferDescriptor& desc) = 0;
                virtual GraphicsBufferSharedPtr Create(const GraphicsBufferDescriptor& desc) = 0;


                FrameBufferSharedPtr current_frame_buffer_;
                
        };
    }  // namespace Rendering
}  // namespace vEngine

extern "C" {
    VENGINE_API void CreateRenderEngine(std::unique_ptr<vEngine::Rendering::RenderEngine>& ptr);
    VENGINE_API void DestoryRenderEngine(std::unique_ptr<vEngine::Rendering::RenderEngine>& ptr);
}
#endif /* _VENGINE_RENDERING_RENDER_ENGINE_HPP */
