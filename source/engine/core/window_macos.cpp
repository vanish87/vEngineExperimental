#ifdef VENGINE_PLATFORM_APPLE
#include <vengine/core/window.hpp>
// #include <xcb/xcb.h>

namespace vEngine
{
    namespace Core
    {
        Window::Window(const WindowDescriptor& desc)
        {
            this->wnd_ = desc.wnd;
            // this->window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
        }
        Window::~Window() {}
        void Window::Update() {}
    }  // namespace Core
}  // namespace vEngine

#endif