#ifndef _VENGINE_CORE_APPLICATION_HPP
#define _VENGINE_CORE_APPLICATION_HPP

#pragma once

#include <VENGINE_API.h>

#include <vengine/core/iruntime_module.hpp>

namespace vEngine
{
    namespace Core
    {
        class VENGINE_API Application : public IRuntimeModule
        {
            public:
                Application(){};
                virtual ~Application(){};

            public:
                virtual void Init(void* wnd);
                virtual void Init() override;
                virtual void Update() override;
                virtual void Deinit() override;
                
                virtual void Run();
                virtual void Quit(bool quit);

            public:
                WindowPtr CurrentWindow();

            protected:
                WindowPtr window_;

            private:
                virtual void OnCreate();
                virtual void OnUpdate();
                virtual void OnDestory();

                virtual void InitInternal(void* wnd);
                bool shouldQuit;
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_APPLICATION_HPP */
