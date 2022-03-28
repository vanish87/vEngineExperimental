
/// \file scene_manager.cpp
/// \brief source file for Scene Manager
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/scene_manager.hpp>
#include <vengine/core/game_node.hpp>

#include <vengine/core/mesh_renderer_component.hpp>

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

                auto mp = std::make_shared<Rendering::MeshRendererComponent>();
                // mp->game_object_ = std::make_shared<Rendering::MeshRenderer>();
                // auto mp = std::make_shared<MeshRendererComponent>();
                // auto mp = std::make_shared<MeshComponent>();
                SceneManager::GetInstance().AddToSceneRoot(mp);
		}
        void SceneManager::Deinit() {}
        void SceneManager::Update()
        {
            auto nodes = std::vector<GameNode*>();
            this->root_.Traverse<GameNode>([&](GameNode* n) {
                nodes.push_back(n);
                return true;
            });

            for (const auto& n : nodes)
            {
                // find render component in root
                n->ForEach<IComponent>([&](IComponent* c) {
                    PRINT("IComponent");
                    auto renderer = dynamic_cast<Rendering::MeshRendererComponent*>(c);
                    if (renderer != nullptr)
                    {
                        PRINT("MeshRendererComponent");
                        // add IRenderer to render queue
                        this->render_queue_.push(renderer->game_object_.get());
                    }
                });
            }

            while (!this->render_queue_.empty())
            {
                auto& r = this->render_queue_.front();
                this->render_queue_.pop();

                r->Render();
            }
        }

        void SceneManager::AddToSceneRoot(const GameNodeSharedPtr newNode)
        {
            this->root_.AddComponent(newNode);
        }
    }  // namespace Core

}  // namespace vEngine