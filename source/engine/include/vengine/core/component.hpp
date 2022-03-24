/// \file component.hpp
/// \brief Head file for Game Component
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_COMPONENT_HPP
#define _VENGINE_CORE_COMPONENT_HPP

#pragma once
#include <VENGINE_API.h>

#include <memory>
#include <vengine/core/game_node.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        Interface VENGINE_API IComponent
        {
        protected:
            virtual ~IComponent(){};
        };

        /// \brief Component model
        ///
        /// Unity-like Component model attached
        /// as game node in the scene
        template <typename T>
        class VENGINE_API Component : public GameNode, public IComponent
        {
            public:
                /// \brief brief constructor description.
                Component(){};
                virtual ~Component(){};

                std::shared_ptr<T> game_object_;
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_COMPONENT_HPP */
