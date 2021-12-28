
#include <iostream>
#include <vengine/rendering/opengl_render_engine.hpp>
namespace vEngine
{
    namespace Rendering
    {
        void OpenGLRenderEngine::TestFunc(){

        };

        void OpenGLRenderEngine::Render(){

        };
        RenderEngine* Create()
        {
            std::cout << "OPENGL" << std::endl;

            return new OpenGLRenderEngine();
        }
    }  // namespace Rendering
}  // namespace vEngine