#ifndef _VENGINE_CORE_IRUNTIME_MODULE_HPP
#define _VENGINE_CORE_IRUNTIME_MODULE_HPP

#pragma once
#include <engine.hpp>

namespace vEngine
{
    namespace Core
    {
        Interface IRuntimeModule
        {
        public:
            virtual void Init() = 0;
            virtual void Deinit() = 0;
            virtual void Update() = 0;
        };

    }  // namespace Core

}  // namespace vEngine

#endif /* _VENGINE_CORE_IRUNTIME_MODULE_HPP */
