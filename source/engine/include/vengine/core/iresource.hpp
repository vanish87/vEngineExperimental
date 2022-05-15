#ifndef _VENGINE_CORE_IRESOURCE_HPP
#define _VENGINE_CORE_IRESOURCE_HPP

#pragma once
#include <functional>
#include <VENGINE_API.hpp>

namespace vEngine
{
    namespace Core
    {
        Interface VENGINE_API IResource: public std::enable_shared_from_this<IResource>
        {
        public:
            virtual bool Load() = 0;
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_IRESOURCE_HPP */
