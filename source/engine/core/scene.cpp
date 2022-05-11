
/// \file scene.cpp
/// \brief source file for Scene
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/scene.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vengine/core/camera_component.hpp>
#include <vengine/core/material.hpp>
#include <vengine/core/mesh_renderer_component.hpp>
#include <vengine/core/resource_loader.hpp>
#include <vengine/core/mesh.hpp>
// #include <vengine/rendering/render_engine.hpp>
/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {
        /// constructor detailed defintion,
        /// should be 2 lines
        Scene::Scene(const std::string file_name) 
		{
			this->file_name_ = file_name;
			this->root_ = std::make_shared<GameNode>();
		}
        bool Scene::Load()
        {
			this->AddTestNode();

            Assimp::Importer importer;
            auto pScene = importer.ReadFile(this->file_name_, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
            this->HandleNode(pScene->mRootNode, pScene, this->root_);
            return true;
        }
        MeshSharedPtr Scene::HandleMeshNode(const aiMesh* mesh, const aiScene* scene)
        {
            UNUSED_PARAMETER(scene);

            auto hasPos = mesh->HasPositions();
            auto hasUV = mesh->HasTextureCoords(0);
            auto hasNormal = mesh->HasNormals();

			std::vector<Vertex> vd;
			std::vector<uint32_t> id;

            for (uint32_t i = 0; i < mesh->mNumVertices; ++i)
            {
                Vertex v;
                v.pos = hasPos ? float3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z) : float3(0, 0, 0);
                // v.pos *= 0.2f;
                // v.pos.z() = 0;
                v.normal = hasNormal ? float3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z) : float3(0, 0, 0);
                v.uv = hasUV ? float2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y) : float2(0, 0);
                v.color = float4(1, 1, 1, 1);

                vd.emplace_back(v);
            }

            for (uint32_t i = 0; i < mesh->mNumFaces; ++i)
            {
                auto f = mesh->mFaces[i];
                for (uint32_t fi = 0; fi < f.mNumIndices; ++fi)
                {
                    id.emplace_back(f.mIndices[fi]);
                }
            }

			return std::make_shared<Mesh>(vd, id);
        }
        bool Scene::HandleNode(const aiNode* node, const aiScene* scene, const GameNodeSharedPtr parent)
        {
            if (node->mNumMeshes > 0)
            {
                auto mesh = scene->mMeshes[node->mMeshes[0]];
                this->HandleMeshNode(mesh, scene);
                return true;
            }


            for (uint32_t c = 0; c < node->mNumChildren; ++c)
            {
                if (this->HandleNode(node->mChildren[c], scene)) return true;
            }

            return false;
        }
		void Scene::Update()
		{
            // camera
            // frame
            // flush each scene object
            // render each matrial pass for every object
            this->root_->Traverse<GameNode>(
                [&](GameNodeSharedPtr node, const GameNodeSharedPtr parent)
                {
                    node->UpdateLocal(parent);
                    return true;
                });

            this->root_->Traverse<CameraComponent>(
                [&](CameraComponentSharedPtr c)
                {
                    c->OnBeginCamera();

                    auto cam = c->game_object_;
                    auto frameBuffer = cam->target;
                    auto& re = Context::GetInstance().GetRenderEngine();
                    re.Bind(frameBuffer);
                    this->Flush();
                    // render all game node
                    // PRINT("Camera");

                    return true;
                });
		}
		void Scene::Flush()
		{
            this->root_->Traverse<MeshRendererComponent>(
                [&](MeshRendererComponentSharedPtr n, const GameNodeSharedPtr parent)
                {
                    n->UpdateComponent(parent);
                    n->OnBeginRender();
                    if (n->game_object_ != nullptr)
                    {
                        n->game_object_->Render();
                    }
                    // Render other renderers(transparent, particle etc.) if possible
                    return true;
                });
		}
        void Scene::AddTestNode()
        {
            auto vs_file = "shader/vs.hlsl";
            auto ps_file = "shader/ps.hlsl";
            auto mat = std::make_shared<Material>(vs_file, ps_file);
            mat->Load();

            auto gn = std::make_shared<GameNode>();

            auto mrc = std::make_shared<Rendering::MeshRendererComponent>();
            mrc->game_object_->material_ = mat;
            gn->AddComponent(mrc);
            auto mc = std::make_shared<Rendering::MeshComponent>();
            mc->game_object_->Load("bunny.obj");
            gn->AddComponent(mc);

            auto s = 2.0f;
            gn->SetScale(float3(s,s,s));
            gn->SetPos(float3(0.1f,0,1));
            // mp->game_object_ = std::make_shared<Rendering::MeshRenderer>();
            // auto mp = std::make_shared<MeshRendererComponent>();
            // auto mp = std::make_shared<MeshComponent>();
            this->AddToSceneNode(gn);

            auto camera = std::make_shared<CameraComponent>();
            camera->game_object_->target = Context::GetInstance().GetRenderEngine().back_buffer_;
            this->AddToSceneNode(camera);
        }
        void Scene::AddToSceneNode(const GameNodeSharedPtr new_node, const GameNodeSharedPtr game_node)
        {
            auto camera = std::dynamic_pointer_cast<CameraComponent>(new_node);
            if (camera != nullptr)
            {
                this->scene_cameras_.emplace_back(camera);
            }

            if (game_node == nullptr)
            {
                this->root_->AddChild(new_node);
            }
            else
            {
                this->root_->Traverse<GameNode>(
                    [&](GameNodeSharedPtr n)
                    {
                        if (n == game_node)
                        {
                            n->AddChild(new_node);
                            return false;
                        }
                        return true;
                    });
            }
        }
    }  // namespace Core

}  // namespace vEngine