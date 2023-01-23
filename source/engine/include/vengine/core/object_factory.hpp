/// \file game_object_factory.hpp
/// \brief Head file for Game Object Factory
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_OBJECT_FACTORY_HPP
#define _VENGINE_CORE_OBJECT_FACTORY_HPP

#pragma once

#include <engine.hpp>

/// A brief namespace description.
namespace vEngine
{
    /// \brief A brief class description.
    ///
    /// A detailed class description, it
    /// should be 2 lines at least.
    namespace Core
    {
        /// \brief To create component and call Init for it
        ///
        class VENGINE_API ObjectFactory
        {
            public:
                template <class... Args>
                virtual GameObjectSharedPtr Create(Args&&... args) = 0;
        } 
        class VENGINE_API RenderFactory : public ObjectFactory
        {
        }

        class VENGINE_API GameObjectFactory : public ObjectFactory
        {
        }
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_OBJECT_FACTORY_HPP */
