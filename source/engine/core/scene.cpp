
/// \file scene.cpp
/// \brief source file for Scene
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/camera_component.hpp>
#include <vengine/core/material.hpp>
#include <vengine/core/mesh.hpp>
#include <vengine/core/mesh_renderer_component.hpp>
#include <vengine/core/resource_loader.hpp>
#include <vengine/core/scene.hpp>
#include <vengine/core/transform_component.hpp>
#include <vengine/core/game_node_factory.hpp>
// #include <vengine/rendering/render_engine.hpp>
/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {
        /// constructor detailed defintion,
        /// should be 2 lines
        Scene::Scene(const std::string file_name) : GameNode()
        {
            this->file_name_ = file_name;
            this->name_ = file_name;
            // this->root_ = std::make_shared<GameNode>();
        }

        bool Scene::Load()
        {
            // this->AddTestNode();

            Assimp::Importer importer;
            auto scene = importer.ReadFile(this->file_name_, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
            this->CreateMeshes(scene);
            this->CreateMaterials(scene);
            this->CreateCameras(scene);

            auto root = this->HandleNode(scene->mRootNode, scene);
            root->name_ = "Assimp Root";
            this->AddChild(root);

            // auto root = ComponentFactory::Create<TransformComponent>();
            // root->name_ = "SceneRoot";
            // this->AddChild(root);


            // auto trans = std::make_shared<TransformComponent>();
            // trans->game_object_->Translate() = float3(0, 0, 0);
            // this->AttachComponent(trans);

            auto s = 2.0f;
            auto root_transform = std::dynamic_pointer_cast<TransformNode>(root);
            root_transform->Transform()->Scale() = float3(s, s, s);
            root_transform->Transform()->Translate() = float3(0.2f, 0, 1);
            return true;
        }
        void Scene::CreateCameras(const aiScene* scene)
        {
            UNUSED_PARAMETER(scene);
            ComponentDescription desc;
            auto camera = GameNodeFactory::Create<CameraComponent>(desc);
            camera->GameObject()->target = Context::GetInstance().GetRenderEngine().back_buffer_;
            this->scene_cameras_.emplace_back(camera);

            GameNodeDescription gndesc;
            gndesc.type = GameNodeType::Transform;
            auto gn = GameNodeFactory::Create(gndesc);
            gn->AttachComponent(camera);
            this->AddChild(gn);

            PRINT("num of cameras: " << this->scene_cameras_.size());
        }
        void Scene::CreateMaterials(const aiScene* scene)
        {
            for (uint32_t mid = 0; mid < scene->mNumMaterials; ++mid)
            {
                // auto mat = scene->mMaterials[mid];
                auto vs_file = "shader/vs.hlsl";
                auto ps_file = "shader/ps.hlsl";
                auto mat = std::make_shared<Material>(vs_file, ps_file);
                mat->Load();
                this->scene_materials_.emplace_back(mat);
            }
            if (this->scene_materials_.size() == 0)
            {
                PRINT("no materials for scene, add a default material");
                auto vs_file = "shader/vs.hlsl";
                auto ps_file = "shader/ps.hlsl";
                auto mat = std::make_shared<Material>(vs_file, ps_file);
                mat->Load();
                this->scene_materials_.emplace_back(mat);
            }
            PRINT("num of materials: " << this->scene_materials_.size());
        }
        void Scene::CreateMeshes(const aiScene* scene)
        {
            for (uint32_t mid = 0; mid < scene->mNumMeshes; ++mid)
            {
                auto mesh = scene->mMeshes[mid];

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
                this->scene_meshes_.emplace_back(std::make_shared<Mesh>(vd, id));
            }

            PRINT("num of meshes: " << this->scene_meshes_.size());
        }
        GameNodeSharedPtr Scene::HandleNode(const aiNode* node, const aiScene* scene)
        {
            GameNodeDescription desc;
            desc.type = GameNodeType::Transform;
            auto game_node = GameNodeFactory::Create(desc);
            // parent->AddChild(game_node);

            for (uint32_t mid = 0; mid < node->mNumMeshes; ++mid)
            {
                auto mesh_node = GameNodeFactory::Create(desc);
                // scene_meshes_ contains same mesh data as they are in aiScene
                auto ai_mesh = scene->mMeshes[mid];

                ComponentDescription cdesc;
                auto mesh = this->scene_meshes_[mid];
                auto mesh_component = GameNodeFactory::Create<MeshComponent>(cdesc, mesh);
                mesh_node->AttachComponent(mesh_component);

                auto mesh_renderer = GameNodeFactory::Create<MeshRendererComponent>(cdesc);
                mesh_node->AttachComponent(mesh_renderer);

                auto mat = this->scene_materials_[ai_mesh->mMaterialIndex];
                mesh_renderer->GameObject()->material_ = mat;

                // auto s = 2.0f;
                // mesh_node->Transform()->Scale() = float3(s, s, s);
                // mesh_node->Transform()->Translate() = float3(0, 0, 1);

                game_node->AddChild(mesh_node);
            }

            for (uint32_t c = 0; c < node->mNumChildren; ++c)
            {
                auto child = this->HandleNode(node->mChildren[c], scene);
                game_node->AddChild(child);
            }

            return game_node;
        }
        void Scene::Update()
        {
            this->TraverseAllChildren<TransformComponent>(
                [&](TransformComponentSharedPtr node)
                {
                    // node->UpdateLocal(parent);
                    node->OnUpdate();

                    // auto pos = node->game_object_->Translate();
                    // PRINT(pos.x() << " " << pos.y());
                    // PRINT(node->name_);
                    return true;
                });
            // camera
            // frame
            // flush each scene object
            // render each matrial pass for every object
            // this->root_->UpdateLocal(nullptr);
            // this->Traverse<GameNode>(
            //     [&](GameNodeSharedPtr node, const GameNodeSharedPtr parent)
            //     {
            //         // node->UpdateLocal(parent);
            //         return true;
            //     });

            for (auto& c : this->scene_cameras_)
            {
                c->OnBeginCamera();

                auto cam = c->GameObject();
                auto frameBuffer = cam->target;
                auto& re = Context::GetInstance().GetRenderEngine();
                re.Bind(frameBuffer);
                this->Flush();
                // render all game node
                // PRINT("Camera");
            }
        }
        void Scene::Flush()
        {
            this->TraverseAllChildren<MeshRendererComponent>(
                [&](MeshRendererComponentSharedPtr n)
                {
                    n->OnUpdate();

                    n->OnBeginRender();
                    if (n->GameObject() != nullptr)
                    {
                        n->GameObject()->Render();
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
            mrc->GameObject()->material_ = mat;
            gn->AttachComponent(mrc);
            auto mc = std::make_shared<Rendering::MeshComponent>();
            mc->GameObject()->Load("bunny.obj");
            gn->AttachComponent(mc);

            // auto s = 2.0f;
            // gn->SetScale(float3(s,s,s));
            // gn->SetPos(float3(0.1f,0,1));
            // mp->game_object_ = std::make_shared<Rendering::MeshRenderer>();
            // auto mp = std::make_shared<MeshRendererComponent>();
            // auto mp = std::make_shared<MeshComponent>();
            this->AddToSceneNode(gn);

            auto camera = std::make_shared<CameraComponent>();
            camera->GameObject()->target = Context::GetInstance().GetRenderEngine().back_buffer_;
            this->AddToSceneNode(camera);
        }
        void Scene::AddToSceneNode(const GameNodeSharedPtr new_node, const GameNodeSharedPtr game_node /*= nullptr*/)
        {
            auto camera = std::dynamic_pointer_cast<CameraComponent>(new_node);
            if (camera != nullptr)
            {
                this->scene_cameras_.emplace_back(camera);
            }

            if (game_node == nullptr)
            {
                this->AddChild(new_node);
            }
            else
            {
                // this->Traverse<GameNode>(
                //     [&](GameNodeSharedPtr n)
                //     {
                //         if (n == game_node)
                //         {
                //             n->AddChild(new_node);
                //             return false;
                //         }
                //         return true;
                //     });
            }
        }
    }  // namespace Core

}  // namespace vEngine