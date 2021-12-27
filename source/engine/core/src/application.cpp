
#include <iostream>
#include <vengine/core/application.hpp>
#include <vengine/core/debug.hpp>

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
        void Application::Deinit(...)
        {
        }
        void Application::Update(float dt)
        {
            UNUSED_PARAMETER(dt);
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
            this->Deinit();
        }

        void Application::OnCreate() {}
        void Application::OnUpdate() {}
        void Application::OnDestory() {}
        void Application::SetupWindow() {}
    }  // namespace Core
}  // namespace vEngine