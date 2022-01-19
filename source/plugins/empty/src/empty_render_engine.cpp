
#include <vengine/rendering/empty_render_engine.hpp>

namespace vEngine
{
    namespace Rendering
    {

        void EmptyRenderEngine::TestFunc() {}

        void EmptyRenderEngine::CreateRenderWindow(void* hwnd)
        {
            UNUSED_PARAMETER(hwnd);
        }
        void EmptyRenderEngine::Render() {}
        void EmptyRenderEngine::PrintInfo()
        {
            std::cout << "Empty" << std::endl;
        }

    }  // namespace Rendering
}  // namespace vEngine

extern "C" {
    void CreateRenderEngine(std::unique_ptr<vEngine::Rendering::RenderEngine>& ptr)
    {
        ptr = std::make_unique<vEngine::Rendering::EmptyRenderEngine>();
    }
    void DestoryRenderEngine(std::unique_ptr<vEngine::Rendering::RenderEngine>& ptr)
    {
        ptr.reset();
    }
}