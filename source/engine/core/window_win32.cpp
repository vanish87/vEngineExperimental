
#ifdef VENGINE_PLATFORM_WINDOWS

    // #include <windows.h>
    // #include <vengine/core/debug.hpp>

    // include windows.h first
    #include <vengine/core/window.hpp>
    #include <vengine/core/application.hpp>
    #include <vengine/core/context.hpp>
// #include <tchar.h>//wchar

namespace vEngine
{
    namespace Core
    {
        void* Window::WindowHandle()
        {
            return this->wnd_;
        }
        void Window::Init(...)
        {
            const auto configure = Context::GetInstance().CurrentConfigure();
            std::string win_name = configure.app_name;

            HINSTANCE hInstance = ::GetModuleHandle(nullptr);

            WNDCLASS wcex = {0};
            wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;  // CS_OWNDC to create own device context
            wcex.lpfnWndProc = WndProc;
            wcex.hInstance = hInstance;
            wcex.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
            // wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
            wcex.lpszClassName = win_name.c_str();
            ::RegisterClass(&wcex);

            RECT rc = {0, 0, configure.graphics_configure.width, configure.graphics_configure.height};
            // get real window size; should slightly bigger than rendering
            // resolution we should render a frame with render_setting, so
            // window is enlarged.
            ::AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

            int top = CW_USEDEFAULT;
            int left = CW_USEDEFAULT;
            int width = rc.right - rc.left;
            int height = rc.bottom - rc.top;
            this->wnd_ = CreateWindow(wcex.lpszClassName, win_name.c_str(), WS_OVERLAPPEDWINDOW, left, top, width, height, nullptr, nullptr, hInstance, nullptr);

            ::ShowWindow(this->wnd_, SW_SHOWNORMAL);
            // ::SetForegroundWindow(this->wnd_);
            // ::SetFocus(this->wnd_);
            //::ShowCursor(!render_setting.full_screen);
            // ::UpdateWindow(this->wnd_);

            // Not used for now
            // ::SetWindowLongPtr(this->wnd_, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
        }
        void Window::Deinit(...) {}
        void Window::Update()
        {
            MSG msg = {0};

            if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
            }
        }
        LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
        {
            switch (uMsg)
            {
                case WM_DESTROY:
                {
                    Context::GetInstance().AppInstance().Quit(true);
                    PostQuitMessage(0);
                    return 0;
                }
                case WM_PAINT:
                {
                    // maybe Render call here
                }
                break;
                case WM_KEYDOWN:
                {
                    // Do input event here
                }
                break;
            }
            return ::DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }  // namespace Core
}  // namespace vEngine

#endif