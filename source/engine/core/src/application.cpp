
#include <iostream>
#include <vengine/core/application.hpp>

namespace vEngine
{
    namespace Core
    {
        void Application::Init()
        {
            // Context::GetInstance().RegisterAppInstance(*this);
            // Make window
            this->CreateWindow();
            // Context::RenderFactory().CreateRenderWindow();
        }
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
        }

        void Application::OnCreate() {}
        void Application::OnUpdate() {}
        void Application::OnDestory() {}
        void Application::CreateWindow() {}
    }  // namespace Core
}  // namespace vEngine