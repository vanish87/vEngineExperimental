#ifndef _VENGINE_RENDERING_OPENGL_RENDER_ENGINE_HPP
#define _VENGINE_RENDERING_OPENGL_RENDER_ENGINE_HPP
#pragma once

#define GLFW_INCLUDE_NONE
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
                void TestFunc();
                void CreateRenderWindow() override;
                void Render() override;
                void PrintInfo() override;
            private:
                GLFWwindow* window;
        };

        // extern "C" {
        //     VENGINE_API RenderEngine* Create(void);
        // }
    }  // namespace Rendering
}  // namespace vEngine
#endif /* _VENGINE_RENDERING_OPENGL_RENDER_ENGINE_HPP */
