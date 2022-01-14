
#ifdef VENGINE_PLATFORM_LINUX
    #include <vengine/core/window.hpp>
	// #include <xcb/xcb.h>

namespace vEngine
{
    namespace Core
    {
        void Window::Init(...) 
		{
            // this->window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
		}
        void Window::Deinit(...) {}
        void Window::Update() {}
    }  // namespace Core
}  // namespace vEngine

#endif