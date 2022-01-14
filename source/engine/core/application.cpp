
#include <memory>
#include <vengine/core/window.hpp>  //windows.h should include first in win32 platform

#include <vengine/core/application.hpp>
#include <vengine/core/context.hpp>

namespace vEngine
{
    namespace Core
    {
        void Application::Init(...)
        {
            Context::GetInstance().RegisterAppInstance(this);
            // Load Dll etc.
            Context::GetInstance().Setup();

            // Make window
            // Platform dependent
            this->SetupWindow();

            // Context::RenderFactory().CreateRenderWindow();

            this->OnCreate();
        }
        void Application::Deinit(...)
        {
            this->OnDestory();
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

            while (!this->shouldQuit)
            {
                this->Update();

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
            this->window_ = std::make_shared<Window>();
            this->window_->Init();
        }
        void Application::Quit(bool quit)
        {
            this->shouldQuit = quit;
        }

    }  // namespace Core
}  // namespace vEngine