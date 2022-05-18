
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

		/// \brief To create component and call Init for it
		/// 
        class ComponentFactory
        {
            public:
                template <typename T>
                static std::shared_ptr<T> Create()
                {
                    static_assert(std::is_base_of<IComponent, T>::value, "T must derived from IComponent");
                    auto gn = std::make_shared<T>();
					auto com = std::dynamic_pointer_cast<IComponent>(gn);
					com->OnInit();
                    return gn;
                }
        };

    }  // namespace Core

}  // namespace vEngine

#endif /* _VENGINE_CORE_COMPONENT_FACTORY_HPP */
