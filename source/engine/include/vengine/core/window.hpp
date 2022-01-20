#ifndef _VENGINE_CORE_WINDOW_HPP
#define _VENGINE_CORE_WINDOW_HPP

#pragma once

#ifdef VENGINE_PLATFORM_WINDOWS
    #include <windows.h>
#elif VENGINE_PLATFORM_LINUX
// OpenGL rendering plugin will create glwindow when creating rendering window
// so this is a empty window in linux platform
// TODO use x11 window later
// struct GLFWwindow;

#endif

#include <VENGINE_API.h>
#include <vengine/core/iruntime_module.hpp>

namespace vEngine
{
    namespace Core
    {
        class VENGINE_API Window : public IRuntimeModule
        {
            public:
                Window() {}
                virtual ~Window() {}
                virtual void Init() override;
                virtual void Deinit() override;
                virtual void Update() override;

            public:
                void* WindowHandle();

            private:
                void* wnd_;
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_WINDOW_HPP */
