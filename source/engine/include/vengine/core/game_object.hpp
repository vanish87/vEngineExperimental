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
            // Core
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

            // Data
            Serializer,

            // Rendering
            Renderer,
            RendererComponent,
            MeshRenderer,
            MeshRendererComponent,
            Material,
            Texture,
            GraphicsBuffer,
            PipelineState,
            Shader,

            // Animation
            Bone,
            BoneComponent,
            Joint,
            AnimationClip,
            Animator,
            AnimatorComponent,

            Custom,
        };

        class GameObjectDescriptor
        {
                friend class GameObject;
                friend class ResourceManager;

            private:
                UUID uuid;
                std::string name = "GameObject";
                GameObjectType type = GameObjectType::GameObject;
                std::string context;
                std::filesystem::path reference_path;

            protected:
                const std::filesystem::path AbsolutePath() const;
                const std::filesystem::path ReferencePath() const;
                const UUID UUID() const;

            public:
                constexpr static auto properties()
                {
                    return std::make_tuple(
                        property("uuid", &GameObjectDescriptor::uuid), 
                        property("name", &GameObjectDescriptor::name), 
                        property("type", &GameObjectDescriptor::type),
                        property("context", &GameObjectDescriptor::context), 
                        property("ref_path", &GameObjectDescriptor::reference_path));
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
                // GameObject(const GameObjectType type = GameObjectType::GameObject);
                // GameObject(const GameObjectType type);
                // GameObject(const GameObject& other);
                // GameObject(const GameObject&& other);
                virtual ~GameObject();

            public:
                const UUID& UUID() const
                {
                    return this->descriptor_.uuid;
                }
                void SetName(const std::string name = "GameObject")
                {
                    this->descriptor_.name = name;
                }
                const std::string Name() const
                {
                    return this->descriptor_.name;
                }
                const GameObjectType Type() const
                {
                    return this->descriptor_.type;
                }
                void SetType(const GameObjectType type)
                {
                    this->descriptor_.type = type;
                }

                void UpdateReferencePath();
                const std::filesystem::path AbsolutePath() const;
                const std::filesystem::path ReferencePath() const;

                constexpr static auto properties()
                {
                    return std::make_tuple(property("meta", &GameObject::descriptor_));
                }

                public:
                    /// \brief conpare all element of vector
                    bool operator==(const GameObject& other) const noexcept
                    {
                        return this->UUID() == other.UUID();
                    }

                protected:
                    const virtual std::filesystem::path GetHierarchyPath() const;

                private:
                    GameObjectDescriptor descriptor_;
        };
    }  // namespace Core
}  // namespace vEngine
namespace std
{
    template <>
    struct hash<vEngine::Core::GameObjectSharedPtr>
    {
            vEngine::uint64_t operator()(vEngine::Core::GameObjectSharedPtr const& value) const
            {
                hash<vEngine::uint64_t> HashFunc;
                return HashFunc(value->UUID().AsUint());
            }
    };
}  // namespace std

#endif /* _VENGINE_CORE_GAME_OBJECT_HPP */
