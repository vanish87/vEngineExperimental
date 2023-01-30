#ifndef _VENGINE_CORE_IRESOURCE_HPP
#define _VENGINE_CORE_IRESOURCE_HPP

#pragma once
#include <engine.hpp>
#include <functional>

namespace vEngine
{
    namespace Core
    {
        struct ResourceDescriptor
        {
                std::function<GameObjectSharedPtr()> on_load_call_back;
        };

        // Interface VENGINE_API IResource
        // {
        // public:
            // virtual bool Load(const ResourceDescriptorSharedPtr descriptor) = 0;
            // virtual ResourceState CurrentState() = 0;
        // };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_IRESOURCE_HPP */
