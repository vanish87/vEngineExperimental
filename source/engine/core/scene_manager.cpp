
/// \file scene_manager.cpp
/// \brief source file for Scene Manager
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/scene_manager.hpp>
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
        void SceneManager::Init()
        {
            // this->root_ = std::make_shared<GameNode>();
            // this->scene_ = std::make_shared<Scene>("cornell-box.obj");
            this->scene_ = std::make_shared<Scene>("bunny.obj");
            this->scene_->Load();

        }
        void SceneManager::Deinit() 
        {
            this->scene_.reset();
        }
        void SceneManager::BeginScene()
        {
            // Update lights constant buffer here
        }
        void SceneManager::Flush()
        {
            this->scene_->Flush();
        }
        void SceneManager::Update()
        {
            this->scene_->Update();
        }


    }  // namespace Core

}  // namespace vEngine