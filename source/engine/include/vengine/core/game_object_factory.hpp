/// \file game_object_factory.hpp
/// \brief Head file for Game Object Factory
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_GAME_OBJECT_FACTORY_HPP
#define _VENGINE_CORE_GAME_OBJECT_FACTORY_HPP

#pragma once

#include <engine.hpp>
#include <vengine/core/game_object.hpp>

/// A brief namespace description.
namespace vEngine
{
    /// \brief A brief class description.
    ///
    /// A detailed class description, it
    /// should be 2 lines at least.
    namespace Core
    {
        enum class GameObjectType
        {
            Raw,
            Transform,
            Camera,
            Mesh,
            // Mesh_Cube,
            Material,
            Bone,
            Joint,
            AnimationClip
        };

        struct GameObjectDescription
        {
                GameObjectType type;
        };

        /// \brief To create component and call Init for it
        ///
        class GameObjectFactory
        {
            public:
                template <typename T, class... Args>
                static std::shared_ptr<T> Create(const GameObjectDescription& desc, Args&&... args)
                {
                    switch (desc.type)
                    {
                    case GameObjectType::Raw:
                        break;
                    // case GameObjectType::Mesh_Cube:
                    // {
                    //     static_assert(std::is_base_of<GameObject, T>::value, "T must derived from GameObject");
                    //     auto gn = std::make_shared<T>(std::forward<Args>(args)...);
                    // }
                    //     break;
                    default:
                        break;
                    }

                    static_assert(std::is_base_of<GameObject, T>::value, "T must derived from GameObject");
                    auto gn = std::make_shared<T>(std::forward<Args>(args)...);
                    return gn;
                }

                // static GameNodeSharedPtr Create(const GameNodeDescription& desc);
                // static TransformNodeSharedPtr Create();
        };

    }  // namespace Core

}  // namespace vEngine

#endif /* _VENGINE_CORE_GAME_OBJECT_FACTORY_HPP */

