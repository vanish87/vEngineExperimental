#ifndef _VENGINE_CORE_WINDOW_HPP
#define _VENGINE_CORE_WINDOW_HPP

#pragma once

#ifdef VENGINE_PLATFORM_WINDOWS
    #include <windows.h>
#elif VENGINE_PLATFORM_UNIX
// OpenGL rendering plugin will create glwindow when creating rendering window
// so this is a empty window in linux platform
// TODO use x11 window later
// struct GLFWwindow;

#endif

#include <VENGINE_API.hpp>

namespace vEngine
{
    namespace Core
    {
        class VENGINE_API Window
        {
            public:
                Window() {}
                virtual ~Window() {}
                virtual void Init(void* wnd) ;
                virtual void Deinit();
                virtual void Update();

            public:
                void* WindowHandle();

            private:
                void* wnd_;

                #ifdef VENGINE_PLATFORM_WINDOWS
                static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

                LRESULT CALLBACK MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
                WNDPROC default_wnd_proc_;
                #endif
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_WINDOW_HPP */
