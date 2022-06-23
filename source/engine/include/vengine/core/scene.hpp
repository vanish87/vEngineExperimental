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
#include <unordered_set>

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
        // using namespace Rendering;
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class Scene : public GameNode//, public IResource
        {

            public:
                /// \brief brief constructor description.
                Scene();
                void LoadFile(const std::string file);

                // bool Load() override;
                // ResourceState CurrentState() override;

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

                // GameNodeSharedPtr HandleNode(const aiNode* node, const aiScene* scene);
                // void CreateMeshes(const aiScene* scene);
                // void CreateMaterials(const aiScene* scene, const std::string current_path);
                // void CreateTextures(const aiScene* scene);
                // void CreateCameras(const aiScene* scene);
                // void CreateAnimations(const aiScene* scene);

                // GameNodeSharedPtr MakeTransformNode();

                // void HandleBoneNode(const aiNode* node, const GameNodeSharedPtr game_node);
                // bool IsRootBone(const aiNode* node, Animation::BoneSharedPtr& joint_found);
                // void AttachToMesh(const GameNodeSharedPtr skeleton, const std::string name);

                void Print();

            private:
                // ResourceState state_;
                // std::string file_path_;

                // std::unordered_set<std::string> file_list_;


                //map mesh to it skeleton
                //<mesh_name, <joint_name, joint>>
                // std::unordered_map<std::string, std::unordered_map<std::string, Animation::JointSharedPtr>> mesh_joints_;
                // std::unordered_map<std::string, Animation::JointSharedPtr> mesh_root_joint_;
        };

    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_SCENE_HPP */
