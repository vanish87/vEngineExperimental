/// \file scene.hpp
/// \brief Head file for Scene Node
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_SCENE_HPP
#define _VENGINE_CORE_SCENE_HPP

#pragma once

#include <unordered_map>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <engine.hpp>
#include <vengine/core/game_node.hpp>
#include <vengine/core/iresource.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class Scene : public GameNode, public IResource
        {
            public:
                /// \brief brief constructor description.
                Scene(const std::string file_name);

                bool Load() override;
                ResourceState CurrentState() override;

				void Update();
				void Flush();

                /// class variable description
                // int public_variable_;

            public:
                /// \brief A brief function description.
                ///
                /// \param p1 Description for p1.
                /// \param p2 Description for p2.
                /// \return Description for return value.
                // int GetVariable(int p1, float p2);
                void AddToSceneNode(const GameNodeSharedPtr new_node, const GameNodeSharedPtr game_node = nullptr);
                void AddTestNode();

                GameNodeSharedPtr HandleNode(const aiNode* node, const aiScene* scene);
                void CreateMeshes(const aiScene* scene);
                void CreateMaterials(const aiScene* scene);
                void CreateCameras(const aiScene* scene);

                GameNodeSharedPtr MakeTransformNode();

            private:
                ResourceState state_;
                std::string file_name_;

                std::vector<CameraComponentSharedPtr> scene_cameras_;
                std::vector<LightComponentSharedPtr> scene_lights_;
                std::vector<MeshSharedPtr> scene_meshes_;
                std::vector<MaterialSharedPtr> scene_materials_;
				
        };

    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_SCENE_HPP */
