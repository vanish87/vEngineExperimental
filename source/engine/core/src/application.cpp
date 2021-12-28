
#include <vengine/core/window.hpp>//windows.h should include first in win32 platform
#include <memory>
#include <vengine/core/application.hpp>
#include <vengine/core/context.hpp>

namespace vEngine
{
    namespace Core
    {
        void Application::Init(...)
        {
            auto ptr = std::shared_ptr<Application>(this);
            Context::GetInstance().RegisterAppInstance(ptr);
            Context::GetInstance().Setup();
            // Make window
            this->SetupWindow();
            // Context::RenderFactory().CreateRenderWindow();

            this->OnCreate();
        }
        void Application::Deinit(...) {}
        void Application::Update() {}
        void Application::Run()
        {
            while (!this->shouldQuit)
            {
                this->window_.get()->Update();
                this->OnUpdate();
                // Context::Update();

                //call here or PAINT event in Winodw Class
                // Render::Flush();
            }

            this->OnDestory();
            this->Deinit();
        }

        void Application::OnCreate() {}
        void Application::OnUpdate() {}
        void Application::OnDestory() {}
        void Application::SetupWindow()
        {
            this->window_ = std::make_shared<Window>();
            this->window_.get()->Init();
        }

    }  // namespace Core
}  // namespace vEngine