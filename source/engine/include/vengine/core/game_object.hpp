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

#include <VENGINE_API.hpp>

#include <vengine/core/uuid.hpp>
#include <vengine/data/meta.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class VENGINE_API GameObject
        {
            public:
                /// \brief brief constructor description.
                GameObject();
                virtual ~GameObject();

                // uuid
                UUID uuid_;
                std::string name_;
                // type?
                constexpr static auto properties()
                {
                    return std::make_tuple(
                        property("uuid", &GameObject::uuid_),
                        property("name", &GameObject::name_)
                    );
                }
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_GAME_OBJECT_HPP */
