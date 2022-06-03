
/// \file game_node_factory.hpp
/// \brief Head file for Game Node and related-node Factory
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
#include "vengine/core/component.hpp"

/// A brief namespace description.
namespace vEngine
{
    /// \brief A brief class description.
    ///
    /// A detailed class description, it
    /// should be 2 lines at least.
    namespace Core
    {
        enum class GameNodeType
        {
            Raw,
            Transform,
            Skeleton,
            Joint,
            Camera,
        };
        enum class ComponentType
        {
            Transform,
            Camera,
            MeshRenderer,
        };
        // template<typename T>
        struct ComponentDescription
        {
                ComponentType type;
        };
        struct GameNodeDescription
        {
                GameNodeType type;
        };

        /// \brief To create component and call Init for it
        ///
        class GameNodeFactory
        {
            public:
                template <typename T, class... Args>
                static std::shared_ptr<T> Create(const ComponentDescription& desc, Args&&... args)
                {
                    switch (desc.type)
                    {
                        case ComponentType::Transform:
                            break;

                        default:
                            break;
                    }

                    static_assert(std::is_base_of<IComponent, T>::value, "T must derived from IComponent");
                    auto gn = std::make_shared<T>(std::forward<Args>(args)...);
                    auto comp = std::dynamic_pointer_cast<GameNode>(gn);
                    comp->name_ = typeid(T).name();
                    return gn;
                }

                static GameNodeSharedPtr Create(const GameNodeDescription& desc);
                // static TransformNodeSharedPtr Create();
        };

    }  // namespace Core

}  // namespace vEngine

#endif /* _VENGINE_CORE_COMPONENT_FACTORY_HPP */
