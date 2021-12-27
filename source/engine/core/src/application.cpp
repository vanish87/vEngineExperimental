
#include <vengine/core/window.hpp>//windows.h should include first in win32 platform
#include <vengine/core/application.hpp>

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
#ifdef VENGINE_PLATFORM_WINDOWS
            MSG msg = {0};
            while (WM_QUIT != msg.message)
#elif VENGINE_PLATFORM_LINUX
            while (true)
#endif
            {
#ifdef VENGINE_PLATFORM_WINDOWS
                if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
#endif

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
            this->window_ = std::make_shared<Window>();
            this->window_.get()->Init();
        }

    }  // namespace Core
}  // namespace vEngine