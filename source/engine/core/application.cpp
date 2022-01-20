
#include <vengine/core/window.hpp>  //windows.h should include first in win32 platform
// #include <memory>
#include <vengine/core/application.hpp>
#include <vengine/core/configure.hpp>
#include <vengine/core/constants.hpp>
#include <vengine/core/context.hpp>
#include <vengine/core/timer.hpp>
#include <vengine/rendering/render_engine.hpp>

namespace vEngine
{
    namespace Core
    {
        void Application::Init()
        {
            Context::GetInstance().RegisterAppInstance(this);

            auto configure = Context::GetInstance().CurrentConfigure();
            // Load Dll etc.
            Context::GetInstance().ConfigureWith(configure);

            // Make window
            this->SetupWindow();

            this->OnCreate();
        }
        void Application::Deinit()
        {
            this->OnDestory();

            // Destory RenderEngine etc;

            // Destory Window

            // Destory Context

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
                while (lag >= TIME_PER_UPDATE)
                {
                    this->Update();

                    // Context::Instance().GetStateManager().Update();
                    // Context::Instance().GetSceneManager().Update();

                    lag -= TIME_PER_UPDATE;
                }

                // call here or PAINT event in Winodw Class
                //  Render::Flush();
            }

            this->Deinit();
        }

        void Application::OnCreate() {}
        void Application::OnUpdate() {}
        void Application::OnDestory() {}
        void Application::SetupWindow()
        {
            // Platform dependent
            this->window_ = std::make_shared<Window>();
            this->window_->Init();

            const auto graphics_configure = Context::GetInstance().CurrentConfigure().graphics_configure;
            Context::GetInstance().GetRenderEngine().CreateRenderWindow(this->window_->WindowHandle(), graphics_configure.width, graphics_configure.height);
        }
        void Application::Quit(bool quit)
        {
            this->shouldQuit = quit;
        }

    }  // namespace Core
}  // namespace vEngine