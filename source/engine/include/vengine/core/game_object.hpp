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

#include <engine.hpp>
#include <vengine/core/uuid.hpp>
#include <vengine/core/game_object_factory.hpp>
#include <vengine/data/meta.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        enum class GameObjectType
        {
            //Core
            GameObject,
            GameNode,
            Component,
            Transform,
            TransformComponent,
            Camera,
            CameraComponent,
            Light,
            LightComponent,
            Mesh,
            MeshComponent,
            
            Serializer,
            Scene,

            //Rendering
            Renderer,
            RendererComponent,
            MeshRenderer,
            MeshRendererComponent,
            Material,
            Texture,

            //Animation
            Bone,
            BoneComponent,
            Joint,
            AnimationClip,
            Animator,
            AnimatorComponent,

        };

        struct GameObjectDescription
        {
                UUID uuid;
                std::string name = "GameObject";
                GameObjectType type = GameObjectType::GameObject;
                std::string context;
                constexpr static auto properties()
                {
                    return std::make_tuple(
                        property("name", &GameObjectDescription::name),
                        property("type", &GameObjectDescription::type),
                        property("context", &GameObjectDescription::context),
                        property("uuid", &GameObjectDescription::uuid)
                    );
                }
        };
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class VENGINE_API GameObject
        {
            public:
                /// \brief brief constructor description.
                GameObject(const GameObjectType type = GameObjectType::GameObject);
                // GameObject(const GameObjectType type);
                // GameObject(const GameObject& other);
                // GameObject(const GameObject&& other);
                virtual ~GameObject();

                GameObjectDescription description_;
                constexpr static auto properties()
                {
                    return std::make_tuple(
                        property("description", &GameObject::description_)
                    );
                }
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_GAME_OBJECT_HPP */
