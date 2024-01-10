
#ifdef VENGINE_PLATFORM_WINDOWS

    // #include <windows.h>
    // #include <vengine/core/debug.hpp>

    // include windows.h first
    #include <vengine/core/window.hpp>
    #include <vengine/core/context.hpp>
// #include <vengine/core/application.hpp>
// #include <tchar.h>//wchar

namespace vEngine
{
    namespace Core
    {
        LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
        {
            auto win_ptr = reinterpret_cast<Window*>(::GetWindowLongPtrW(hWnd, GWLP_USERDATA));
            if (win_ptr != nullptr)
            {
                return win_ptr->MsgProc(hWnd, message, wParam, lParam);
            }
            return ::DefWindowProc(hWnd, message, wParam, lParam);
        }
        LRESULT Window::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
        {
            switch (message)
            {
                case WM_DESTROY:
                {
                    //TODO Use Event/Observer Pattern to decouple context class
                    Context::GetInstance().QuitApplication();
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

            return this->default_wnd_proc_(hWnd, message, wParam, lParam);
        }
        Window::Window(const WindowDescriptor& desc)
        {
            std::string win_name = desc.name;

            auto hwnd = static_cast<HWND>(desc.wnd);
            if (hwnd != nullptr)
            {
                this->default_wnd_proc_ = reinterpret_cast<WNDPROC>(::GetWindowLongPtrW(hwnd, GWLP_WNDPROC));
            }
            else
            {
                HINSTANCE hInstance = ::GetModuleHandle(nullptr);

                WNDCLASS wcex = {0};
                wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;  // CS_OWNDC to create own device context
                wcex.lpfnWndProc = WndProc;
                wcex.hInstance = hInstance;
                wcex.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
                // wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
                wcex.lpszClassName = win_name.c_str();
                ::RegisterClass(&wcex);

                RECT rc = {0, 0, desc.width, desc.height};
                // get real window size; should slightly bigger than rendering
                // resolution we should render a frame with render_setting, so
                // window is enlarged.
                ::AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

                int top = CW_USEDEFAULT;
                int left = CW_USEDEFAULT;
                int width = rc.right - rc.left;
                int height = rc.bottom - rc.top;

                // VE_INFO("Window size " << width << " " << height);

                hwnd = CreateWindow(wcex.lpszClassName, win_name.c_str(), WS_OVERLAPPEDWINDOW, left, top, width, height, nullptr, nullptr, hInstance, nullptr);
                VE_ASSERT_PTR_NOT_NULL(hwnd);
                ::ShowWindow(hwnd, SW_SHOWNORMAL);

                this->default_wnd_proc_ = ::DefWindowProc;
            }

            ::SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
            this->wnd_ = hwnd;
            // ::SetForegroundWindow(this->wnd_);
            // ::SetFocus(this->wnd_);
            //::ShowCursor(!render_setting.full_screen);
            // ::UpdateWindow(this->wnd_);
        }
        Window::~Window()
        {
            ::DestroyWindow(static_cast<HWND>(this->wnd_));
        }
        void Window::Update()
        {
            MSG msg;
            if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
            }
        }
    }  // namespace Core
}  // namespace vEngine

#endif