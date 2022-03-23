
/// \file scene_manager.cpp
/// \brief source file for Scene Manager
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

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
        void SceneManager::Init() {}
        void SceneManager::Deinit() {}
        void SceneManager::Update()
        {
			//find render component in root
			//add IRenderer to render queue
            // this->render_queue_.push(renderer);

			while (!this->render_queue_.empty())
			{
				auto& r = this->render_queue_.front();
				this->render_queue_.pop();

				r.Render();
			}
			
        }

        void SceneManager::AddToSceneRoot(const GameNodeSharedPtr newNode)
        {
            this->root_ = newNode;
        }
    }  // namespace Core

}  // namespace vEngine