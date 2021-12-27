
#include <iostream>
#include <vengine/core/application.hpp>
#include <vengine/core/debug.hpp>
#include <vengine/core/window.hpp>

namespace vEngine
{
    namespace Core
    {
        void Application::Init(...)
        {
            // Context::GetInstance().RegisterAppInstance(*this);
            // Make window
            this->SetupWindow();
            // Context::RenderFactory().CreateRenderWindow();

            this->OnCreate();
        }
        void Application::Deinit(...) {}
        void Application::Update() {}
        void Application::Run()
        {
#ifdef WINDOWS
            while (true)
#elif LINUX
            while (true)
#endif
            {
                this->OnUpdate();
                // Context::Update();

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
            this->window_ = std::shared_ptr<Window>();
        }

    }  // namespace Core
}  // namespace vEngine