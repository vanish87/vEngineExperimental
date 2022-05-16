/// \file transform_component.hpp
/// \brief Head file for Transform Component
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_TRANSFORM_COMPONENT_HPP
#define _VENGINE_CORE_TRANSFORM_COMPONENT_HPP

#pragma once

#include <VENGINE_API.hpp>
#include <vengine/core/component.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        template <typename T>
        class VENGINE_API TransformComponent : public Component<Transform>
        {
            public:
                /// \brief brief constructor description.
                TransformComponent(){};
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_TRANSFORM_COMPONENT_HPP */
