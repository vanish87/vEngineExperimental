/// \file light_component.hpp
/// \brief Head file for Light Component
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_LIGHT_COMPONENT_HPP
#define _VENGINE_CORE_LIGHT_COMPONENT_HPP

#pragma once

#include <engine.hpp>
#include <vengine/core/component.hpp>
#include <vengine/core/light.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class LightComponent : public Component<Light>
        {
            public:
                /// \brief brief constructor description.
                LightComponent(const GameObjectType type = GameObjectType::LightComponent);
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_LIGHT_COMPONENT_HPP */
