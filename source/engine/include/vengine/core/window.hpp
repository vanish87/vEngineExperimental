#ifndef _VENGINE_CORE_WINDOW_HPP
#define _VENGINE_CORE_WINDOW_HPP

#pragma once

// #ifdef VENGINE_PLATFORM_WINDOWS
//     #define NOMINMAX
//     #include <windows.h>
// #ifdef VENGINE_PLATFORM_UNIX
// OpenGL rendering plugin will create glwindow when creating rendering window
// so this is a empty window in linux platform
// TODO use x11 window later
// struct GLFWwindow;
// #endif

#include <engine.hpp>
#include <vengine/core/event/event.hpp>

namespace vEngine
{
    namespace Core
    {
        struct WindowDescriptor
        {
            std::string name;
            void* wnd;
            int width;
            int height;
        };
        class VENGINE_API Window
        {
            public:
                Window(const WindowDescriptor& desc);
                virtual ~Window();

                void Update();

            public:
                void* WindowHandle()
                {
                    return this->wnd_;
                };

            private:
                void* wnd_;

                //EventCallback Here

                #ifdef VENGINE_PLATFORM_WINDOWS
                static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

                LRESULT CALLBACK MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
                WNDPROC default_wnd_proc_;
                #endif
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_WINDOW_HPP */
