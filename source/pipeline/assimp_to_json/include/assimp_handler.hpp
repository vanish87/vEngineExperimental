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

#include <filesystem>

// #pragma clang diagnostic ignored "-Wmicrosoft-enum-value"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
// #pragma clang diagnostic warning "-Wmicrosoft-enum-value"

#include <engine.hpp>
#include <vengine/core/application.hpp>

namespace vEngine
{
    namespace Pipeline
    {
        class AssimpHandler: public Core::Application
        {
            public:
                Core::SceneSharedPtr LoadFromAssimp(const std::filesystem::path path);

            private:
                Core::float4x4 AiMatrixToFloat4x4(aiMatrix4x4 mat);
                void HandleCameras(Core::SceneSharedPtr scene, const aiScene* ai_scene);
                void HandleMaterials(Core::SceneSharedPtr scene, const aiScene* ai_scene);
                void HandleMeshes(Core::SceneSharedPtr scene, const aiScene* ai_scene);
                void HandleAnimations(Core::SceneSharedPtr scene, const aiScene* ai_scene);
                void HandleAnimator(Core::SceneSharedPtr scene, const aiScene* ai_scene);
                Core::GameNodeSharedPtr HandleNode(Core::SceneSharedPtr scene, const aiNode* ai_node, const aiScene* ai_scene);
                void HandleBoneNode(Core::SceneSharedPtr scene, const aiNode* ai_node, const Core::GameNodeSharedPtr game_node);
        };
    }  // namespace Pipeline
}  // namespace vEngine

#endif /* _ASSIMP_TO_JSON_INCLUDE_ASSIMP_HANDLER_HPP */
