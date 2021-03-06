#ifndef _VENGINE_RENDERING_OPENGL_RENDER_ENGINE_HPP
#define _VENGINE_RENDERING_OPENGL_RENDER_ENGINE_HPP
#pragma once

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <vengine/rendering/render_engine.hpp>

namespace vEngine
{
    namespace Rendering
    {

        class OpenGLRenderEngine : public RenderEngine
        {
            public:
                OpenGLRenderEngine()
                {
                    PRINT("Create OpenGL");
                }
                ~OpenGLRenderEngine()
                {
                    PRINT("Destructor OpenGL");
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
                GLFWwindow* window;

            private:
                void InitPipline();
                void DebugTriangleDraw();
                void DeinitPipline();
                GLuint vertex_buffer, vertex_shader, fragment_shader, program;
                GLint mvp_location, vpos_location, vcol_location;
        };

        // extern "C" {
        //     VENGINE_API RenderEngine* Create(void);
        // }
    }  // namespace Rendering
}  // namespace vEngine
#endif /* _VENGINE_RENDERING_OPENGL_RENDER_ENGINE_HPP */
