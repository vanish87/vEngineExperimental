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

#include <engine.hpp>
#include <filesystem>

struct aiNode;
struct aiScene;

namespace vEngine
{
    namespace Pipeline
    {
        class AssimpHandler
        {
            public:
                SceneSharedPtr LoadFromAssimp(const std::filesystem::path path);

            private:
                void HandleCameras(const aiScene* scene);
                void HandleMaterials(const aiScene* scene);
                void HandleMeshes(const aiScene* scene);
                void HandleAnimations(const aiScene* scene);
        };
    }  // namespace Pipeline
}  // namespace vEngine

#endif /* _ASSIMP_TO_JSON_INCLUDE_ASSIMP_HANDLER_HPP */
