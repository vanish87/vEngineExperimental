#ifndef _VENGINE_CORE_WINDOW_HPP
#define _VENGINE_CORE_WINDOW_HPP

#pragma once

#ifdef VENGINE_PLATFORM_WINDOWS
    #include <windows.h>
#elif VENGINE_PLATFORM_LINUX
struct GLFWwindow;

#endif

#include <CORE_API.h>

// #include <engine.hpp>
#include <vengine/core/iruntime_module.hpp>

namespace vEngine
{
    namespace Core
    {
        class CORE_API Window : public IRuntimeModule
        {
            public:
                virtual ~Window() {}
                virtual void Init(...) override;
                virtual void Deinit(...) override;
                virtual void Update() override;

#ifdef VENGINE_PLATFORM_WINDOWS
            private:
                static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
                HWND wnd_;
                // LRESULT CALLBACK MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
                // WNDPROC default_wnd_proc_;
#elif VENGINE_PLATFORM_LINUX
private:

    GLFWwindow* window;


#endif
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_WINDOW_HPP */
