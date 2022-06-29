/// \file asset.hpp
/// \brief Head file for asset game object
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_ASSET_HPP
#define _VENGINE_CORE_ASSET_HPP

#pragma once
#include <vector>
#include <unordered_map>

#include <engine.hpp>
#include <vengine/core/iresource.hpp>
#include <vengine/core/game_object.hpp>

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
        /// should be 2 lines at least.
        class Asset : public GameObject, public IResource
        {
            public:
                /// \brief brief constructor description.
                Asset();
                virtual ~Asset();
                bool Load(const ResourceDescriptor& descriptor) override;
                ResourceState CurrentState() override;

                const GameNodeSharedPtr GetRoot() const;
                const CameraSharedPtr GetCamera(const uint32_t index = 0) const;
                const std::vector<Animation::AnimationClipSharedPtr> GetAnimations() const;

            private:
                ResourceState current_state_;

                std::vector<CameraSharedPtr> cameras_;
                std::vector<LightSharedPtr> lights_;
                std::unordered_map<int, MeshSharedPtr> meshes_;
                std::unordered_map<std::string, Rendering::TextureSharedPtr> textures_;
                std::vector<MaterialSharedPtr> materials_;
                std::vector<Animation::AnimationClipSharedPtr> animation_clips_;

                GameNodeSharedPtr root_;

                GameNodeSharedPtr HandleNode(const aiNode* node, const aiScene* scene);
                void HandleCameras(const aiScene* scene);
                void HandleMaterials(const aiScene* scene);
                void HandleMeshes(const aiScene* scene);
                void HandleAnimations(const aiScene* scene);
                void HandleBoneNode(const aiNode* node, const GameNodeSharedPtr game_node);

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

#endif /* _VENGINE_CORE_ASSET_HPP */
