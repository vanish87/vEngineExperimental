/// \file iresource.hpp
/// \brief Head file for Resource Interface
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_IRESOURCE_HPP
#define _VENGINE_CORE_IRESOURCE_HPP

#pragma once
#include <functional>
#include <engine.hpp>

namespace vEngine
{
    namespace Core
    {
        struct ResourceDescriptor
        {
                std::function<GameObjectSharedPtr()> on_load_call_back;

                // std::function<GameObjectSharedPtr()> on_load_call_back;
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
