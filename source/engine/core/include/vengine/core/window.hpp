#ifndef _WINDOW_HPP
#define _WINDOW_HPP

#pragma once

#include <CORE_API.h>

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
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _WINDOW_HPP */
