
/// \file scene_manager.cpp
/// \brief source file for Scene Manager
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/camera_component.hpp>
#include <vengine/core/context.hpp>
#include <vengine/core/game_node.hpp>
#include <vengine/core/material.hpp>
#include <vengine/core/mesh_renderer_component.hpp>
#include <vengine/core/resource_loader.hpp>
#include <vengine/core/scene_manager.hpp>
#include <vengine/rendering/render_engine.hpp>
/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {

        /// constructor detailed defintion,
        /// should be 2 lines
        SceneManager::SceneManager() {}
        SceneManager::~SceneManager() {}
        void SceneManager::Init()
        {
            this->root_ = std::make_shared<GameNode>();

            this->AddTestNode();
        }
        void SceneManager::AddTestNode()
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
            mc->game_object_->Load("cube.obj");
            gn->AddComponent(mc);

            gn->SetScale(float3(0.5f, 0.5f, 0.5f));
            // mp->game_object_ = std::make_shared<Rendering::MeshRenderer>();
            // auto mp = std::make_shared<MeshRendererComponent>();
            // auto mp = std::make_shared<MeshComponent>();
            SceneManager::GetInstance().AddToSceneNode(gn);

            auto camera = std::make_shared<CameraComponent>();
            camera->game_object_->target = Context::GetInstance().GetRenderEngine().back_buffer_;
            SceneManager::GetInstance().AddToSceneNode(camera);
        }
        void SceneManager::Deinit() {}
        void SceneManager::BeginScene()
        {
            // Update lights constant buffer here
        }
        void SceneManager::Flush()
        {
            this->root_->Traverse<MeshRendererComponent>(
                [&](MeshRendererComponentSharedPtr n, const GameNodeSharedPtr parent)
                {
                    n->Update(parent);
                    n->OnBeginRender();
                    if (n->game_object_ != nullptr)
                    {
                        n->game_object_->Render();
                    }
                    // Render other renderers(transparent, particle etc.) if possible
                    return true;
                });
        }
        void SceneManager::Update()
        {
            // camera
            // frame
            // flush each scene object
            // render each matrial pass for every object

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

        void SceneManager::AddToSceneNode(const GameNodeSharedPtr new_node, const GameNodeSharedPtr game_node)
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