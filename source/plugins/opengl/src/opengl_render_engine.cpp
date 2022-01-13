
#include <iostream>
#include <vengine/core/application.hpp>
#include <vengine/core/context.hpp>
#include <vengine/rendering/opengl_render_engine.hpp>
namespace vEngine
{
    namespace Rendering
    {
        static void error_callback(int error, const char* description)
        {
            UNUSED_PARAMETER(error);
            fprintf(stderr, "Error: %s\n", description);
        }

        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            UNUSED_PARAMETER(scancode);
            UNUSED_PARAMETER(mods);
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
                Core::Context::GetInstance().AppInstance().Quit(true);

                glfwDestroyWindow(window);
                glfwTerminate();
            }
        }

        void OpenGLRenderEngine::TestFunc() {}
        void OpenGLRenderEngine::CreateRenderWindow()
        {
            glfwSetErrorCallback(error_callback);

            if (!glfwInit()) exit(EXIT_FAILURE);

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

            window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
            if (!window)
            {
                glfwTerminate();
                exit(EXIT_FAILURE);
            }

            glfwSetKeyCallback(window, key_callback);

            glfwMakeContextCurrent(window);
        }

        void OpenGLRenderEngine::Render() {}
        RenderEngine* Create()
        {
            std::cout << "OPENGL" << std::endl;

            auto ret = new OpenGLRenderEngine();
            // ret->CreateRenderWindow();
            return ret;
        }
    }  // namespace Rendering
}  // namespace vEngine