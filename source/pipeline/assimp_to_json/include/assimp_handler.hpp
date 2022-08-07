/// \file assimp_handler.hpp
/// \brief Head file for class assimp_handler
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _ASSIMP_TO_JSON_INCLUDE_ASSIMP_HANDLER_HPP
#define _ASSIMP_TO_JSON_INCLUDE_ASSIMP_HANDLER_HPP

#pragma once

#include <vector>
#include <unordered_map>

#include <engine.hpp>

struct aiNode;
struct aiScene;

namespace vEngine
{
    namespace Pipeline
    {
        class AssimpHandler
        {
                std::vector<Core::CameraSharedPtr> cameras_;
                std::vector<Core::LightSharedPtr> lights_;
                std::unordered_map<int, Core::MeshSharedPtr> meshes_;
                std::unordered_map<std::string, Rendering::TextureSharedPtr> textures_;
                std::vector<Rendering::MaterialSharedPtr> materials_;
                std::vector<Animation::AnimationClipSharedPtr> animation_clips_;
            public:
                void HandleCameras(const aiScene* scene);
                void HandleMaterials(const aiScene* scene);
                void HandleMeshes(const aiScene* scene);
                void HandleAnimations(const aiScene* scene);
        }

    }  // namespace Pipeline
}  // namespace vEngine

#endif /* _ASSIMP_TO_JSON_INCLUDE_ASSIMP_HANDLER_HPP */
