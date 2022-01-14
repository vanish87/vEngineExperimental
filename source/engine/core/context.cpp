
#ifdef VENGINE_PLATFORM_WINDOWS
    #include <windows.h>
#endif

#include <engine.hpp>
#include <vengine/core/application.hpp>
#include <vengine/core/context.hpp>
#include <vengine/rendering/render_engine.hpp>

namespace vEngine
{
    typedef void (*CreateRenderEngine)(std::unique_ptr<Rendering::RenderEngine>& ptr);
    namespace Core
    {
        Context::Context() : appInstance{nullptr} {}
        Context::~Context() {}

        /// Load Dll
        /// Create Redering
        void Context::Setup()
        {
            // auto re = Create();
            // UNUSED_PARAMETER(re);

#ifdef VENGINE_PLATFORM_WINDOWS
            auto hGetProcIDDLL = ::LoadLibrary("d3d11_rendering_plugind.dll");
            // auto hGetProcIDDLL = ::LoadLibrary("opengl_rendering_plugind.dll");

            if (!hGetProcIDDLL)
            {
                std::cout << "could not load the dynamic library" << std::endl;
                return;
                // return EXIT_FAILURE;
            }

            // resolve function address here
            auto func = reinterpret_cast<CreateRenderEngine>(::GetProcAddress(hGetProcIDDLL, "CreateRenderEngine"));
            if (!func)
            {
                std::cout << "could not locate the function" << std::endl;
                return;
                // return EXIT_FAILURE;
            }

            func(this->render_engine_ptr_);
            this->render_engine_ptr_->PrintInfo();

            // RenderEngine* re = reinterpret_cast<RenderEngine*>(funci());
            // re->CreateRenderWindow();
#else
            // auto re = Create();
            // UNUSED_PARAMETER(re);

#endif

            PRINT("testjJA");
        }

        void Context::RegisterAppInstance(Application* app)
        {
            // UNUSED_PARAMETER(app);
            this->appInstance = app;
            
        }
        Application& Context::AppInstance() const
        {
            return *(this->appInstance);
        }
    }  // namespace Core
}  // namespace vEngine