#ifndef _APPLICATION_HPP
#define _APPLICATION_HPP

#pragma once

#include <CORE_API.h>
#include <vengine/core/iapplication.hpp>

namespace vEngine
{
    namespace Core
    {
        class CORE_API Application : public IApplication
        {
            public:
                virtual void Run() override;

                virtual void Init(...) override;
                virtual void Deinit(...) override;
                virtual void Update() override;

            private:
                virtual void OnCreate() override;
                virtual void OnUpdate() override;
                virtual void OnDestory() override;

                virtual void SetupWindow() override;
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _APPLICATION_HPP */
