/// \file game_object.hpp
/// \brief Head file for Game Object
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_GAME_OBJECT_HPP
#define _VENGINE_CORE_GAME_OBJECT_HPP

#pragma once

#include <vengine/core/uuid.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class GameObject
        {
            public:
                /// \brief brief constructor description.
                GameObject();

                // uuid
                UUID uuid_;
                // type?
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_GAME_OBJECT_HPP */
