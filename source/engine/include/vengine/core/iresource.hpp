#ifndef _VENGINE_CORE_IRESOURCE_HPP
#define _VENGINE_CORE_IRESOURCE_HPP

#pragma once

namespace vEngine
{
    namespace Core
    {
        Interface IResource
        {
        public:
            virtual bool Load() = 0;
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_IRESOURCE_HPP */
