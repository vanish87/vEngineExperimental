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
        /// \brief To create component and call Init for it
        ///
        class VENGINE_API GameObjectFactory
        {
            public:
                    // if constexpr (Type == etype) return GameObjectFactory::Create<type>(std::forward<Args>(args)...);
                #define TYPE_AND_CREATE(etype, type)                                                        \
                    static_assert(std::is_base_of<GameObject, T>::value, "T must derived from GameObject"); \
                    if constexpr (Type == etype) return std::make_shared<type>(std::forward<Args>(args)...);

                #define RENDERING_TYPE_AND_CREATE(etype, type) \
                    if constexpr (Type == etype) return Context::GetInstance().GetRenderEngine()->Create(std::forward<Args>(args)...);

                template <GameObjectType Type, typename T = GameObject, class... Args>
                static std::shared_ptr<T> Create(Args&&... args)
                {
                    TYPE_AND_CREATE(GameObjectType::GameObject, GameObject);
                    TYPE_AND_CREATE(GameObjectType::GameNode, GameNode);
                    if constexpr (Type == GameObjectType::Component) static_assert(false, "Cannot create component without game object type");
                    TYPE_AND_CREATE(GameObjectType::Transform, Transform);
                    TYPE_AND_CREATE(GameObjectType::TransformComponent, TransformComponent);
                    TYPE_AND_CREATE(GameObjectType::Camera, Camera);
                    TYPE_AND_CREATE(GameObjectType::CameraComponent, CameraComponent);
                    TYPE_AND_CREATE(GameObjectType::Light, Light);
                    TYPE_AND_CREATE(GameObjectType::LightComponent, LightComponent);
                    TYPE_AND_CREATE(GameObjectType::Mesh, Mesh);
                    TYPE_AND_CREATE(GameObjectType::MeshComponent, MeshComponent);
                    TYPE_AND_CREATE(GameObjectType::Scene, Scene);

                    TYPE_AND_CREATE(GameObjectType::Serializer, Data::Serializer);

                    if constexpr (Type == GameObjectType::Renderer) static_assert(false, "Cannot create renderer without renderable type");
                    if constexpr (Type == GameObjectType::RendererComponent) static_assert(false, "Cannot create renderer component without renderable type");
                    TYPE_AND_CREATE(GameObjectType::MeshRenderer, Rendering::MeshRenderer);
                    TYPE_AND_CREATE(GameObjectType::MeshRendererComponent, Rendering::MeshRendererComponent);
                    TYPE_AND_CREATE(GameObjectType::Material, Rendering::Material);
                    RENDERING_TYPE_AND_CREATE(GameObjectType::Texture, Rendering::Texture);
                    RENDERING_TYPE_AND_CREATE(GameObjectType::PipelineState, Rendering::PipelineState);
                    TYPE_AND_CREATE(GameObjectType::Shader, Rendering::Shader);

                    TYPE_AND_CREATE(GameObjectType::Bone, Animation::Bone);
                    TYPE_AND_CREATE(GameObjectType::BoneComponent, Animation::BoneComponent);
                    TYPE_AND_CREATE(GameObjectType::Joint, Animation::Joint);
                    TYPE_AND_CREATE(GameObjectType::AnimationClip, Animation::AnimationClip);
                    TYPE_AND_CREATE(GameObjectType::Animator, Animation::Animator);
                    TYPE_AND_CREATE(GameObjectType::AnimatorComponent, Animation::AnimatorComponent);

                    // if constexpr (Type == GameObjectType::Camera) return Context::GetInstance().CreateTest<Camera>(std::forward<Args>(args)...);
                    // if constexpr (Type == GameObjectType::Light) return Context::GetInstance().CreateTest<Light>(std::forward<Args>(args)...);
                    // if constexpr (Type == GameObjectType::Mesh) return std::make_shared<Mesh>(args);

                    // if constexpr (Type == GameObjectType::Mesh) return std::make_shared<Mesh>();
                    // if constexpr (Type == GameObjectType::Scene) return std::make_shared<Scene>();
                    // if constexpr (Type == GameObjectType::GameObject) return std::make_shared<GameObject>();
                    // if constexpr (Type == GameObjectType::GameNode) return std::make_shared<GameNode>();
                    // return nullptr;
                }

                template <typename T, class... Args>
                static std::shared_ptr<T> Create(Args&&... args)
                {
                    static_assert(std::is_base_of<GameObject, T>::value, "T must derived from GameObject");
                    auto gn = std::make_shared<T>(std::forward<Args>(args)...);
                    auto go = std::dynamic_pointer_cast<GameObject>(gn);
                    go->descriptor_.context = typeid(T).name();
                    // TODO Checking description type with T

                    // Context::GetInstance().Register(go);

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
                static std::shared_ptr<T> Find(const GameObjectDescriptor& desc)
                {
                    auto go = Context::GetInstance().Find(desc.uuid);
                    if (go != nullptr) return std::dynamic_pointer_cast<T>(go);
                    return nullptr;
                }


                // static GameNodeSharedPtr Create(const GameNodeDescription& desc);
                // static TransformNodeSharedPtr Create();
        };

    }  // namespace Core

}  // namespace vEngine

#endif /* _VENGINE_CORE_GAME_OBJECT_FACTORY_HPP */
