
#ifdef VENGINE_PLATFORM_WINDOWS

    // #include <windowsx.h>
    //  #include <vengine/core/debug.hpp>

    // include windows.h first
    #include <vengine/core/window.hpp>
    #include <vengine/core/context.hpp>
    #include <vengine/core/input.hpp>
    #include <vengine/core/event/event.hpp>
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

        static Keyboard ToKeyboard(WPARAM raw)
        {
            switch (raw)
            {
                case VK_ESCAPE:
                    return Keyboard::Escape;
                case 'A':
                    return Keyboard::A;
                case 'B':
                    return Keyboard::B;
                case 'C':
                    return Keyboard::C;
                case 'D':
                    return Keyboard::D;
                case 'E':
                    return Keyboard::E;
                case 'F':
                    return Keyboard::F;
                case 'G':
                    return Keyboard::G;
                case 'H':
                    return Keyboard::H;
                case 'I':
                    return Keyboard::I;
                case 'J':
                    return Keyboard::J;
                case 'K':
                    return Keyboard::K;
                case 'L':
                    return Keyboard::L;
                case 'M':
                    return Keyboard::M;
                case 'N':
                    return Keyboard::N;
                case 'O':
                    return Keyboard::O;
                case 'P':
                    return Keyboard::P;
                case 'Q':
                    return Keyboard::Q;
                case 'R':
                    return Keyboard::R;
                case 'S':
                    return Keyboard::S;
                case 'T':
                    return Keyboard::T;
                case 'U':
                    return Keyboard::U;
                case 'V':
                    return Keyboard::V;
                case 'W':
                    return Keyboard::W;
                case 'X':
                    return Keyboard::X;
                case 'Y':
                    return Keyboard::Y;
                case 'Z':
                    return Keyboard::Z;
                default:
                    break;
            }
            return Keyboard::None;
        }
        static float2 ToNormalizeScreenCordinate(LPARAM raw, int2 screen_size)
        {
            auto pos = int2(GET_X_LPARAM(raw), GET_Y_LPARAM(raw));
            auto npos = float2(pos) / screen_size;
            npos.y() = 1 - npos.y();
            return npos;
        }

        LRESULT Window::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
        {
            switch (message)
            {
                case WM_DESTROY:
                {
                    // TODO Use Event/Observer Pattern to decouple context class
                    const WindowEvent e;
                    Context::GetInstance().Dispath(e);
                    PostQuitMessage(0);
                }
                break;
                case WM_INPUT:
                {
                    // raw input
                }
                break;
                case WM_PAINT:
                {
                    // maybe Render call here
                }
                break;
                case WM_KEYDOWN:
                {
                    const KeyPressedEvent e(ToKeyboard(wParam));
                    Context::GetInstance().Dispath(e);
                }
                break;
                case WM_KEYUP:
                {
                    // Handle key release events
                }
                break;
                case WM_MOUSEMOVE:
                {
                    // Handle mouse move event...
                    const int2 screen_size = int2(this->descriptor_.width, this->descriptor_.height);
                    const auto npos = ToNormalizeScreenCordinate(lParam, screen_size);
                    const MouseMoveEvent e(npos.x(), npos.y());
                    Context::GetInstance().Dispath(e);
                }
                break;
                case WM_LBUTTONDOWN:
                {
                    // const int2 screen_size = int2(this->descriptor_.width, this->descriptor_.height);
                    // const auto npos = ToNormalizeScreenCordinate(lParam, screen_size);
                    const MouseButtonEvent e;
                    Context::GetInstance().Dispath(e);
                }
                break;
            }

            return this->default_wnd_proc_(hWnd, message, wParam, lParam);
        }
        Window::Window(const WindowDescriptor& desc)
        {
            this->descriptor_ = desc;
            std::string win_name = this->descriptor_.name;

            auto hwnd = static_cast<HWND>(this->descriptor_.wnd);
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

                RECT rc = {0, 0, this->descriptor_.width, this->descriptor_.height};
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
            this->descriptor_.wnd = hwnd;
            // ::SetForegroundWindow(this->wnd_);
            // ::SetFocus(this->wnd_);
            //::ShowCursor(!render_setting.full_screen);
            // ::UpdateWindow(this->wnd_);
        }
        Window::~Window()
        {
            ::DestroyWindow(static_cast<HWND>(this->descriptor_.wnd));
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