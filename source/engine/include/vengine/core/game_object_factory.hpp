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
#include <vengine/core/context.hpp>

/// A brief namespace description.
namespace vEngine
{
    /// \brief A brief class description.
    ///
    /// A detailed class description, it
    /// should be 2 lines at least.
    namespace Core
    {
        template <typename T>
        class go_shared_ptr : public std::shared_ptr<T>
        {
            using go_type = T;
        };

        /// \brief To create component and call Init for it
        ///
        class VENGINE_API GameObjectFactory
        {
            public:
                template <typename T, class... Args>
                go_shared_ptr<T> go_make_shared(Args&&... args)
                {
                    static_assert(std::is_base_of<GameObject, T>::value, "T must derived from GameObject");
                    auto go = new T(std::forward<Args>(args)...);
                    go_shared_ptr<T> go_ptr;
                    go_ptr.reset(go);
                    return go_ptr;
                }

                template <typename T, class... Args>
                static std::shared_ptr<T> Create(Args&&... args)
                {
                    // switch (desc.type)
                    // {
                    // case GameObjectType::Raw:
                    //     break;
                    // // case GameObjectType::Mesh_Cube:
                    // // {
                    // //     static_assert(std::is_base_of<GameObject, T>::value, "T must derived from GameObject");
                    // //     auto gn = std::make_shared<T>(std::forward<Args>(args)...);
                    // // }
                    // //     break;
                    // default:
                    //     break;
                    // }

                    static_assert(std::is_base_of<GameObject, T>::value, "T must derived from GameObject");
                    auto gn = std::make_shared<T>(std::forward<Args>(args)...);
                    auto go = std::dynamic_pointer_cast<GameObject>(gn);
                    go->description_.type = typeid(T).name();
                    // TODO Checking description type with T

                    Context::GetInstance().Register(go);

                    return gn;
                }

                template <typename T, class... Args>
                static std::shared_ptr<T> Default(Args&&... args)
                {
                    return T::Default(std::forward<Args>(args)...);
                    // static auto go = std::make_shared<T>();
                    // return go;
                }
                static GameObjectSharedPtr CreateByTypeString(const std::string type);

                template <typename T>
                static std::shared_ptr<T> Find(const GameObjectDescription& desc)
                {
                    auto go = Context::GetInstance().Find(desc.uuid);
                    if (go != nullptr) return std::dynamic_pointer_cast<T>(go);
                    return nullptr;
                }

                template <typename T, class... Args>
                static std::shared_ptr<T> CreateByDesc(const GameObjectDescription& desc, Args&&... args)
                {
                    auto go = CreateByTypeString(desc.type);
                    CHECK_ASSERT_NOT_NULL(go);
                    return std::dynamic_pointer_cast<T>(go);
                }

                // static GameNodeSharedPtr Create(const GameNodeDescription& desc);
                // static TransformNodeSharedPtr Create();
        };

    }  // namespace Core

}  // namespace vEngine

#endif /* _VENGINE_CORE_GAME_OBJECT_FACTORY_HPP */
