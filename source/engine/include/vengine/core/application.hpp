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
                virtual void Init();
                virtual void Run();
                virtual void Quit(bool quit);

            protected:
                WindowPtr window_;

            private:
                virtual void Deinit();
                virtual void Update();

                virtual void OnCreate();
                virtual void OnUpdate();
                virtual void OnDestory();

                virtual void SetupWindow();
                bool shouldQuit;
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_APPLICATION_HPP */
