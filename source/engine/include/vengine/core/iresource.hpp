#ifndef _VENGINE_CORE_IRESOURCE_HPP
#define _VENGINE_CORE_IRESOURCE_HPP

#pragma once
#include <VENGINE_API.hpp>
#include <functional>

namespace vEngine
{
    namespace Core
    {
        enum class ResourceState
        {
            Unknown,
            Loading,
            Loaded,
        };
        Interface VENGINE_API IResource
        {
        public:
            virtual bool Load() = 0;
            virtual ResourceState CurrentState() = 0;
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_IRESOURCE_HPP */
