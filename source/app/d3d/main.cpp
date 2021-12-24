#include <ft2build.h>
// #include <windows.h>

#include <iostream>
#include <lua.hpp>
#include <vector>
#include FT_FREETYPE_H

#include <d3d11.h>
#include <windows.h>

#include <engine.hpp>
#include <string>
#include <version.hpp>

#include "interface.h"

#include <vengine/core/debug.hpp>

using namespace vEngine::Core;
using namespace vEngine::Math;

Vector<int, 2> NewVec()
{
    return Vector<int, 2>();
}

struct WinndowRect
{
        uint16_t top;
        uint16_t left;
        uint16_t width;
        uint16_t height;
};
// typedef int(__stdcall* f_funci)();
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int main(int argc, char* argv[])
{
    UNUSED_PARAMETER(argc);
    UNUSED_PARAMETER(argv);
    
    HINSTANCE hInstance = ::GetModuleHandle(nullptr);

    WinndowRect wind;

    std::string win_name_w = "test";

    WNDCLASS wcex;
    wcex.style = CS_HREDRAW | CS_VREDRAW |
                 CS_OWNDC;  // CS_OWNDC to create own device context
    wcex.lpfnWndProc = WindowProc;
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
    // get real window size; should slightly bigger than rendering resolution
    // we should render a frame with render_setting, so window is enlarged.
    ::AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    wind.top = static_cast<uint16_t>(0);
    wind.left = static_cast<uint16_t>(0);
    wind.width = static_cast<uint16_t>(rc.right - rc.left);
    wind.height = static_cast<uint16_t>(rc.bottom - rc.top);
    auto wnd_ = CreateWindow(win_name_w.c_str(), win_name_w.c_str(),
                     WS_OVERLAPPEDWINDOW, wind.left, wind.top, wind.width,
                     wind.height, nullptr, nullptr, hInstance, nullptr);

    InitD3D(wnd_, 640, 480);
    MSG msg = {0};
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return 0;
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT: {
            // PAINTSTRUCT ps;
            // HDC hdc = BeginPaint(hwnd, &ps);

            //just test issue flowworks
            

            RenderFrame();

            // FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));

            // EndPaint(hwnd, &ps);
        }
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
