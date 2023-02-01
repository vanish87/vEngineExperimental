
/// \file scene_manager.cpp
/// \brief source file for Scene Manager
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx


#include <vengine/core/scene_manager.hpp>

#include <vengine/core/resource_manager.hpp>
#include <vengine/core/scene.hpp>
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
        void SceneManager::Load(const std::string scene_name)
        {
            ResourceDescriptor desc;
            desc.on_load_call_back = [&]()
            {
                auto path = ResourceManager::GetInstance().GetFilePath(scene_name);
                this->scene_ = Scene::Load(path);;
                return this->scene_;
            };             
            ResourceManager::GetInstance().LoadAsync(desc);
        }
        void SceneManager::Init()
        {
        }
        void SceneManager::Deinit()
        {
            this->scene_.reset();
        }
        void SceneManager::BeginScene()
        {
            // Update lights constant buffer here
        }
        void SceneManager::EndScene()
        {

        }
        void SceneManager::Update()
        {
            if (this->scene_ != nullptr) this->scene_->Update();
        }

    }  // namespace Core

}  // namespace vEngine