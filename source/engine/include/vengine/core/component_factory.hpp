
/// \file component_factory.hpp
/// \brief Head file for Component Factory
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_COMPONENT_FACTORY_HPP
#define _VENGINE_CORE_COMPONENT_FACTORY_HPP

#pragma once

#include "engine.hpp"
#include "icomponent.hpp"

/// A brief namespace description.
namespace vEngine
{
    /// \brief A brief class description.
    ///
    /// A detailed class description, it
    /// should be 2 lines at least.
    namespace Core
    {
        // template<typename T>
        struct ComponentDescription
        {
                /* data */
        };

        template <typename T>
        class ComponentFactory
        {
                static_assert(std::is_base_of<IComponent, T>::value, "T must derived from IComponent");

            public:
                static std::shared_ptr<T> Create()
                {
                    auto com = std::make_shared<T>();
                    return com;
                }
        };

    }  // namespace Core

}  // namespace vEngine

#endif /* _VENGINE_CORE_COMPONENT_FACTORY_HPP */
