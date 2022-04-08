
/// \file scene_manager.cpp
/// \brief source file for Scene Manager
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/game_node.hpp>
#include <vengine/core/mesh_renderer_component.hpp>
#include <vengine/core/scene_manager.hpp>

#include <vengine/core/resource_loader.hpp>
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

            auto gn = std::make_shared<GameNode>();
            auto mrc = std::make_shared<Rendering::MeshRendererComponent>();
            gn->AddComponent(mrc);
            auto mc = std::make_shared<Rendering::MeshComponent>();
            // mc->game_object_->Load("MyMesh.obj");
            ResourceLoader::GetInstance().AddAsync(mc->game_object_, [&](IResourceSharedPtr c) {
                PRINT("Resource loaded");
            });

            gn->AddComponent(mc);
            // mp->game_object_ = std::make_shared<Rendering::MeshRenderer>();
            // auto mp = std::make_shared<MeshRendererComponent>();
            // auto mp = std::make_shared<MeshComponent>();
            SceneManager::GetInstance().AddToSceneNode(gn);

        }
        void SceneManager::Deinit() {}
        void SceneManager::Update()
        {
            auto nodes = std::vector<GameNodeSharedPtr>();
            this->root_->Traverse<GameNode>([&](GameNodeSharedPtr n) {
                nodes.push_back(n);
                return true;
            });

            for (const auto& n : nodes)
            {
                // find render component in root
                n->ForEachChild<IComponent>([&](IComponentSharedPtr c) {
                    PRINT("IComponent");
                    //Render mesh
                    auto renderer = std::dynamic_pointer_cast<Rendering::MeshRendererComponent>(c);
                    if (renderer != nullptr)
                    {
                        renderer->Update(n);
                        if(renderer->game_object_ != nullptr)
                        {
                            // add IRenderer to render queue
                            this->render_queue_.push(renderer->game_object_);
                        }
                    }
                    //Render other renderers(transparent, particle etc.) if possible
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