#ifndef _IRUNTIME_MODULE_HPP
#define _IRUNTIME_MODULE_HPP

#pragma once

namespace vEngine
{
    namespace Core
    {
        class IRuntimeModule
        {
            public:
                virtual void Init(...) = 0;
                virtual void Deinit(...) = 0;
                virtual void Update(float dt) = 0;
        };

    }  // namespace Core

}  // namespace vEngine

#endif /* _IRUNTIME_MODULE_HPP */
