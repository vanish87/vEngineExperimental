
#ifdef VENGINE_PLATFORM_UNIX
    #include <vengine/core/window.hpp>
	// #include <xcb/xcb.h>

namespace vEngine
{
    namespace Core
    {
        void* Window::WindowHandle()
        {
            return this->wnd_;
        }
        void Window::Init(void* wnd)
		{
            this->wnd_ = wnd;
            // this->window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
		}
        void Window::Deinit() {}
        void Window::Update() {}
    }  // namespace Core
}  // namespace vEngine

#endif