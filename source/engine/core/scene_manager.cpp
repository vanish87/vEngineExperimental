
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
            auto mat = std::make_shared<Material>("vs", "ps");
            mat->Load();

            auto gn = std::make_shared<GameNode>();
            auto mrc = std::make_shared<Rendering::MeshRendererComponent>();
            mrc->game_object_->material_ = mat;
            gn->AddComponent(mrc);
            auto mc = std::make_shared<Rendering::MeshComponent>();
            mc->game_object_->Load("bunny.obj");
            gn->AddComponent(mc);
            // mp->game_object_ = std::make_shared<Rendering::MeshRenderer>();
            // auto mp = std::make_shared<MeshRendererComponent>();
            // auto mp = std::make_shared<MeshComponent>();
            SceneManager::GetInstance().AddToSceneNode(gn);

            auto camera = std::make_shared<CameraComponent>();
            SceneManager::GetInstance().AddToSceneNode(camera);

        }
        void SceneManager::Deinit() {}
        void SceneManager::Flush()
        {

        }
        void SceneManager::Update()
        {
            //camera
            //frame
            //flush each scene object
            //render each matrial pass for every object

            //get all cameras
            //if camera has target texture
            //render to target
            //bind backbuffer
            //render all none-target camera
            this->root_->Traverse<CameraComponent>([&](CameraComponentSharedPtr c) {
                // auto frameBuffer = c->game_object_->target;
                // auto& re = Context::GetInstance().GetRenderEngine();
                // re.Bind(frameBuffer);
                // render all game node
                // PRINT("Camera");

                return true;
            });
            auto nodes = std::vector<GameNodeSharedPtr>();
            this->root_->Traverse<GameNode>([&](GameNodeSharedPtr n) {
                nodes.push_back(n);
                return true;
            });

            for (const auto& n : nodes)
            {
                // find render component in root
                n->ForEachChild<Rendering::MeshRendererComponent>([&](Rendering::MeshRendererComponentSharedPtr c) {
                    // PRINT("IComponent");
                    // Render mesh
                    // auto renderer = std::dynamic_pointer_cast<Rendering::MeshRendererComponent>(c);
                    // if (renderer != nullptr)
                    {
                        c->Update(n);
                        if (c->game_object_ != nullptr)
                        {
                            // add IRenderer to render queue
                            this->render_queue_.push(c->game_object_);
                        }
                    }
                    // Render other renderers(transparent, particle etc.) if possible
                });

                // n->ForEachChild<IComponent>([&](IComponent* c) {
                //     PRINT("IComponent");
                //     auto renderer = dynamic_cast<Rendering::MeshRendererComponent*>(c);
                //     if (renderer != nullptr)
                //     {
                //         PRINT("MeshRendererComponent");
                //         // add IRenderer to render queue
                //         this->render_queue_.push(renderer->game_object_.get());
                //     }
                // });
            }

            while (!this->render_queue_.empty())
            {
                auto r = this->render_queue_.front();
                this->render_queue_.pop();

                r->Render();
            }
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
                this->root_->Traverse<GameNode>([&](GameNodeSharedPtr n) {
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