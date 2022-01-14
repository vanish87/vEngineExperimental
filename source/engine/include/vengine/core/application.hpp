#ifndef _VENGINE_CORE_APPLICATION_HPP
#define _VENGINE_CORE_APPLICATION_HPP

#pragma once

#include <VENGINE_API.h>

#include <vengine/core/iapplication.hpp>

namespace vEngine
{
    namespace Core
    {
        class VENGINE_API Application : public IApplication
        {
            public:
                Application(){};
                virtual ~Application(){};

            public:
                virtual void Run() override;

                virtual void Init(...) override;
                virtual void Quit(bool quit) override;

            private:
                virtual void Update() override;
                virtual void Deinit(...) override;

                virtual void OnCreate() override;
                virtual void OnUpdate() override;
                virtual void OnDestory() override;

                virtual void SetupWindow() override;
                bool shouldQuit;

        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_APPLICATION_HPP */
