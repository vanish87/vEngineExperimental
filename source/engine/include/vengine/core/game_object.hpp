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

#include <filesystem>

#include <engine.hpp>
#include <vengine/core/uuid.hpp>

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
            Scene,

            //Data
            Serializer,

            //Rendering
            Renderer,
            RendererComponent,
            MeshRenderer,
            MeshRendererComponent,
            Material,
            Texture,
            GraphicsBuffer,
            PipelineState,
            Shader,

            //Animation
            Bone,
            BoneComponent,
            Joint,
            AnimationClip,
            Animator,
            AnimatorComponent,

            Custom,
        };

        struct GameObjectDescriptor
        {
                UUID uuid;
                std::string name = "GameObject";
                GameObjectType type = GameObjectType::GameObject;
                std::string context;
                std::filesystem::path reference_path;
                constexpr static auto properties()
                {
                    return std::make_tuple(
                        property("uuid", &GameObjectDescriptor::uuid),
                        property("name", &GameObjectDescriptor::name),
                        property("type", &GameObjectDescriptor::type),
                        property("context", &GameObjectDescriptor::context),
                        property("ref_path", &GameObjectDescriptor::reference_path)
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

                GameObjectDescriptor descriptor_;
                constexpr static auto properties()
                {
                    return std::make_tuple(
                        property("meta", &GameObject::descriptor_)
                    );
                }
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_GAME_OBJECT_HPP */
