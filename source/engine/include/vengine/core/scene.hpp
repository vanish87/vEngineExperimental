/// \file scene.hpp
/// \brief Head file for Scene game object
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_SCENE_HPP
#define _VENGINE_CORE_SCENE_HPP

#pragma once
#include <vector>
#include <unordered_map>

#include <engine.hpp>
#include <vengine/data/meta.hpp>

#include <vengine/core/iresource.hpp>
#include <vengine/core/game_node.hpp>

struct aiNode;
struct aiScene;

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {

        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        class VENGINE_API Scene : public GameNode
        {
            public:
                constexpr static auto properties()
                {
                    return std::tuple_cat(
                        GameNode::properties(),
                        std::make_tuple(
                            property("meshes", &Scene::meshes_),
                            property("materials", &Scene::materials_),
                            property("textures", &Scene::textures_),
                            property("animations", &Scene::animation_clips_)
                        )
                    );
                }
                static SceneSharedPtr Load(const std::filesystem::path path);
            public:
                /// \brief brief constructor description.
                Scene();
                virtual ~Scene();

                const CameraSharedPtr GetCamera(const uint32_t index = 0) const;
                const std::vector<Animation::AnimationClipSharedPtr> GetAnimations() const;

                void AddCamera(const CameraSharedPtr camera);
                void AddLight(const LightSharedPtr light);
                void AddMaterial(const Rendering::MaterialSharedPtr material);
                void AddAnimation(const Animation::AnimationClipSharedPtr animation_clip);

                void SetMesh(const int id, const MeshSharedPtr mesh);
                void SetTexture(const std::string path, const Rendering::TextureSharedPtr texture);
                bool HasTexture(const std::string path);
                Rendering::TextureSharedPtr GetTexture(const std::string path);

            public:

                std::vector<CameraSharedPtr> cameras_;
                std::vector<LightSharedPtr> lights_;
                std::unordered_map<int, MeshSharedPtr> meshes_;
                std::unordered_map<std::string, Rendering::TextureSharedPtr> textures_;
                std::vector<Rendering::MaterialSharedPtr> materials_;
                std::vector<Animation::AnimationClipSharedPtr> animation_clips_;

                GameNodeSharedPtr HandleNode(const aiNode* node, const aiScene* scene);
                void HandleCameras(const aiScene* scene);
                void HandleMaterials(const aiScene* scene);
                void HandleMeshes(const aiScene* scene);
                void HandleAnimations(const aiScene* scene);
                void HandleBoneNode(const aiNode* node, const GameNodeSharedPtr game_node);

            public:
                void Update();

            private:
                void Flush();
                
            private:
            public:
                /// \brief A brief function description.
                ///
                /// \param p1 Description for p1.
                /// \param p2 Description for p2.
                /// \return Description for return value.
                int GetVariable(int p1, float p2);
        };
    }  // namespace Core

}  // namespace vEngine

#endif /* _VENGINE_CORE_SCENE_HPP */
