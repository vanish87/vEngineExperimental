#ifndef _VENGINE_RENDERING_OPENGL_RENDER_ENGINE_HPP
#define _VENGINE_RENDERING_OPENGL_RENDER_ENGINE_HPP
#pragma once

#define GLFW_INCLUDE_NONE
#define GLAD_GL_IMPLEMENTATION
#include <GLFW/glfw3.h>
#include <glad/gl.h>

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
