
#ifdef VENGINE_PLATFORM_WINDOWS

    // #include <windows.h>
    // #include <vengine/core/debug.hpp>
    #include <vengine/core/window.hpp>
// #include <tchar.h>//wchar

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
        void Window::Init(...)
        {
            HINSTANCE hInstance = ::GetModuleHandle(nullptr);

            WindowRect wind;

            std::string win_name_w = "test";

            WNDCLASS wcex;
            wcex.style = CS_HREDRAW | CS_VREDRAW |
                         CS_OWNDC;  // CS_OWNDC to create own device context
            wcex.lpfnWndProc = WndProc;
            wcex.cbClsExtra = 0;
            wcex.cbWndExtra = 0;
            wcex.hInstance = hInstance;
            wcex.hIcon = nullptr;
            wcex.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
            wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
            wcex.lpszMenuName = nullptr;
            wcex.lpszClassName = win_name_w.c_str();

            RegisterClass(&wcex);

            RECT rc = {0, 0, 640, 480};
            // get real window size; should slightly bigger than rendering
            // resolution we should render a frame with render_setting, so
            // window is enlarged.
            ::AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

            wind.top = static_cast<uint16_t>(0);
            wind.left = static_cast<uint16_t>(0);
            wind.width = static_cast<uint16_t>(rc.right - rc.left);
            wind.height = static_cast<uint16_t>(rc.bottom - rc.top);
            this->wnd_ = CreateWindow(win_name_w.c_str(), win_name_w.c_str(),
                                      WS_OVERLAPPEDWINDOW, wind.left, wind.top,
                                      wind.width, wind.height, nullptr, nullptr,
                                      hInstance, nullptr);
            ::ShowWindow(this->wnd_, SW_SHOWNORMAL);
            ::SetForegroundWindow(this->wnd_);
            ::SetFocus(this->wnd_);
            //::ShowCursor(!render_setting.full_screen);
            ::UpdateWindow(this->wnd_);
        }
        void Window::Deinit(...) {}
        void Window::Update() {

            MSG msg = {0};

                if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
        }
        LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                                         LPARAM lParam)
        {
            switch (uMsg)
            {
                case WM_DESTROY:
                    PostQuitMessage(0);
                    return 0;

                case WM_PAINT: {
                    // PAINTSTRUCT ps;
                    // HDC hdc = BeginPaint(hwnd, &ps);

                    // just test issue flowworks

                    // RenderFrame();

                    // FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));

                    // EndPaint(hwnd, &ps);
                }
                    return 0;
            }
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }  // namespace Core
}  // namespace vEngine

#endif