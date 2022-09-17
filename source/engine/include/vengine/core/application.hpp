#ifndef _VENGINE_CORE_APPLICATION_HPP
#define _VENGINE_CORE_APPLICATION_HPP

#pragma once

#include <engine.hpp>
// #include <vengine/core/iruntime_module.hpp>

namespace vEngine
{
    namespace Core
    {
        class VENGINE_API Application
        {
            public:
                Application();
                virtual ~Application();

            public:
                virtual void Run();
                virtual void Quit();

            private:
                void Init();
                void Update();
                void Deinit();

                virtual void OnInit();
                virtual void OnUpdate();
                virtual void OnDeinit();

                bool should_quit_;
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_APPLICATION_HPP */
