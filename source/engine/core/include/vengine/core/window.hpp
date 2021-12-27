#ifndef _VENGINE_CORE_WINDOW_HPP
#define _VENGINE_CORE_WINDOW_HPP

#pragma once
#ifdef VENGINE_PLATFORM_WINDOWS
    #include <windows.h>
#endif

#include <CORE_API.h>

#include <engine.hpp>
#include <vengine/core/iruntime_module.hpp>

namespace vEngine
{
    namespace Core
    {
        class CORE_API Window : public IRuntimeModule
        {
            public:
                virtual void Init(...) override;
                virtual void Deinit(...) override;
                virtual void Update() override;

#ifdef VENGINE_WINDOWS
            private:
                    // static LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
                    // WPARAM wParam,
                    //                                 LPARAM lParam);
                    // LRESULT CALLBACK MsgProc(HWND hWnd, UINT message, WPARAM
                    // wParam,
                    //                          LPARAM lParam);
                    // // HWND wnd_;
                    // WNDPROC default_wnd_proc_;
#endif
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_WINDOW_HPP */
