
#include <iostream>

#include <vengine/rendering/opengl_render_engine.hpp>
namespace vEngine
{
    namespace Rendering
    {
        void OpenGLRenderEngine::TestFunc() {}
        void OpenGLRenderEngine::CreateRenderWindow()
        {
            window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
            if (!window)
            {
                glfwTerminate();
                exit(EXIT_FAILURE);
            }

            // glfwSetKeyCallback(window, key_callback);

            glfwMakeContextCurrent(window);
        }

        void OpenGLRenderEngine::Render() {}
        RenderEngine* Create()
        {
            std::cout << "OPENGL" << std::endl;

            return new OpenGLRenderEngine();
        }
    }  // namespace Rendering
}  // namespace vEngine