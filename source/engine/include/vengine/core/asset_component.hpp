/// \file asset_component.hpp
/// \brief Head file for asset component
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_ASSET_COMPONENT_HPP
#define _VENGINE_CORE_ASSET_COMPONENT_HPP

#pragma once

#include <engine.hpp>
#include <vengine/core/scene.hpp>
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
        class AssetComponent : public Component<Scene>
        {
            public:
                /// \brief brief constructor description.
                AssetComponent();
                virtual ~AssetComponent();

            public:
                /// \brief A brief function description.
                ///
                /// \param p1 Description for p1.
                /// \param p2 Description for p2.
                /// \return Description for return value.
                int GetVariable(int p1, float p2);
        };
    }  // namespace Core

}  // namespace vEngine

#endif /* _VENGINE_CORE_ASSET_COMPONENT_HPP */
