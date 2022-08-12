
#define NOMINMAX
#include <vengine/core/window.hpp>  //windows.h should include first in win32 platform
// #include <memory>
#include <vengine/core/application.hpp>
#include <vengine/core/configure.hpp>
#include <vengine/core/constants.hpp>
#include <vengine/core/context.hpp>
#include <vengine/core/scene_manager.hpp>
#include <vengine/core/timer.hpp>
#include <vengine/rendering/render_engine.hpp>

namespace vEngine
{
    namespace Core
    {
        vEngineWindowPtr Application::CurrentWindow()
        {
            return this->window_;
        }
        void Application::Init(void* wnd)
        {
            Context::GetInstance().RegisterAppInstance(this);
            // Make window
            // Platform dependent
            this->window_ = std::make_shared<Window>();
            this->window_->Init(wnd);

            Context::GetInstance().GetRenderEngine().Init();
            SceneManager::GetInstance().Init();

            this->OnCreate();
        }
        void Application::Deinit()
        {
            this->OnDestroy();

            // Destroy RenderEngine etc;
            SceneManager::GetInstance().Deinit();
            Context::GetInstance().GetRenderEngine().Deinit();

            // Destroy Window
            this->window_->Deinit();
            this->window_.reset();

            // Destroy Context
            Context::GetInstance().Deinit();
        }
        void Application::Update()
        {
            // Update Window event/messages
            // this is platform dependent
            // Win32 will peek/dispatch window messages
            this->window_->Update();

            // call user update
            this->OnUpdate();

            // update other context module
            //  Context::Update();
            SceneManager::GetInstance().Update();
            SceneManager::GetInstance().Flush();
            // call here or PAINT event in Window Class
            // Context::GetInstance().GetRenderEngine().Update();
        }
        void Application::Run()
        {
            this->shouldQuit = false;

            Timer updateTimer;
            double previous = updateTimer.Time();
            double lag = 0;

            while (!this->shouldQuit)
            {
                double current = updateTimer.Time();
                double elapsed = current - previous;
                previous = current;
                lag += elapsed;

                // Update in constant rate
                // may be changed later
                while (lag >= TIME_PER_UPDATE && !this->shouldQuit)
                {
                    this->Update();
                    lag -= TIME_PER_UPDATE;
                }
            }
            this->Deinit();
        }

        void Application::OnCreate() {}
        void Application::OnUpdate() {}
        void Application::OnDestroy() {}
        void Application::Quit(bool quit)
        {
            this->shouldQuit = quit;
        }

    }  // namespace Core
}  // namespace vEngine