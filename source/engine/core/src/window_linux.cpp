
#ifdef VENGINE_PLATFORM_LINUX
    #include <vengine/core/window.hpp>

namespace vEngine
{
    namespace Core
    {
        struct WindowRect
        {
                int top;
                int left;
                int width;
                int height;
        };
        void Window::Init(...) {}
        void Window::Deinit(...) {}
        void Window::Update() {}
    }  // namespace Core
}  // namespace vEngine

#endif