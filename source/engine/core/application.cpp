
// #define NOMINMAX
// #include <vengine/core/window.hpp>  //windows.h should include first in win32 platform
// #include <memory>
#include <vengine/core/application.hpp>
// #include <vengine/core/configure.hpp>
#include <vengine/core/constants.hpp>
#include <vengine/core/context.hpp>
// #include <vengine/core/scene_manager.hpp>
#include <vengine/core/timer.hpp>
// #include <vengine/rendering/render_engine.hpp>

namespace vEngine
{
    namespace Core
    {
        Application::Application() : should_quit_{false} {}
        Application::~Application() {}
        void Application::Init()
        {
            // Context::GetInstance().RegisterAppInstance(this);
            // Make window
            // Platform dependent
            // this->window_ = std::make_shared<Window>();
            // this->window_->Init(wnd);

            // Context::GetInstance().GetRenderEngine().Init();
            // SceneManager::GetInstance().Init();

            Context::GetInstance().Init();
            Context::GetInstance().RegisterAppInstance(this->shared_from_this());
            this->OnInit();
        }
        void Application::Deinit()
        {
            this->OnDeinit();
            Context::GetInstance().Deinit();

            // Destroy RenderEngine etc;
            // SceneManager::GetInstance().Deinit();
            // Context::GetInstance().GetRenderEngine().Deinit();

            // // Destroy Window
            // this->window_->Deinit();
            // this->window_.reset();
        }
        void Application::Update()
        {
            // Update Window event/messages
            // this is platform dependent
            // Win32 will peek/dispatch window messages
            // this->window_->Update();
            Context::GetInstance().Update();
            // call user update
            this->OnUpdate();

            // update other context module
            //  Context::Update();
            // SceneManager::GetInstance().Update();
            // call here or PAINT event in Window Class
            // Context::GetInstance().GetRenderEngine().Update();
        }
        void Application::RunOnce()
        {
            this->Init();
            this->Update();
            this->Deinit();
        }

        void Application::Run()
        {
            this->Init();

            Timer update_timer;
            auto previous = update_timer.Time();
            auto lag = 0.0;

            while (!this->should_quit_)
            {
                auto current = update_timer.Time();
                auto elapsed = current - previous;
                previous = current;
                lag += elapsed;

                // Update in constant rate
                // may be changed later
                while (lag >= TIME_PER_UPDATE && !this->should_quit_)
                {
                    this->Update();
                    lag -= TIME_PER_UPDATE;
                }
            }
            this->Deinit();
        }

        void Application::OnInit() {}
        void Application::OnUpdate() {}
        void Application::OnDeinit() {}
        void Application::Quit()
        {
            this->should_quit_ = true;
        }

    }  // namespace Core
}  // namespace vEngine