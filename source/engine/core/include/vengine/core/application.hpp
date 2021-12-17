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
				void Run1();
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _APPLICATION_HPP */
