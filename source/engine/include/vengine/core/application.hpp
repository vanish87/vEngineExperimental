#ifndef _VENGINE_CORE_APPLICATION_HPP
#define _VENGINE_CORE_APPLICATION_HPP

#pragma once

#include <VENGINE_API.hpp>

#include <vengine/core/iruntime_module.hpp>

namespace vEngine
{
    namespace Core
    {
        class VENGINE_API Application
        {
            public:
                Application(){};
                virtual ~Application(){};

            public:
                virtual void Init(void* wnd = nullptr);
                virtual void Update();
                virtual void Deinit();
                
                virtual void Run();
                virtual void Quit(bool quit);

            public:
                vEngineWindowPtr CurrentWindow();

            protected:
                vEngineWindowPtr window_;

            private:
                virtual void OnCreate();
                virtual void OnUpdate();
                virtual void OnDestroy();

                bool shouldQuit;
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_APPLICATION_HPP */
