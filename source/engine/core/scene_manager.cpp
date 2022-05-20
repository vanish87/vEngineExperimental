
/// \file scene_manager.cpp
/// \brief source file for Scene Manager
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <external/lodepng.h>

#include <vengine/core/resource_loader.hpp>
#include <vengine/core/scene.hpp>
#include <vengine/core/scene_manager.hpp>
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
            ResourceLoader::GetInstance().LoadAsync(this->scene_,
            [&](IResourceSharedPtr c)
            {
                UNUSED_PARAMETER(c);
                PRINT("Resource loaded");
            });
            // this->scene_->Load();

            // std::vector<byte> out;
            // uint32_t width;
            // uint32_t height;

            // auto error = lodepng::decode(out, width, height, "sponza/textures/background.png");

            // PRINT(error);
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
            if (this->scene_->CurrentState() == ResourceState::Loaded)
            {
                this->scene_->Update();
            }
        }

    }  // namespace Core

}  // namespace vEngine