
#ifdef VENGINE_PLATFORM_WINDOWS
    #include <windows.h>
typedef int(__stdcall *f_funci)();
#include <engine.hpp>
#else
#include <engine.hpp>
extern "C" {
    vEngine::Core::RenderEngine* Create();
}
#endif
#include <vengine/core/application.hpp>
#include <vengine/core/context.hpp>
#include <vengine/rendering/render_engine.hpp>

namespace vEngine
{
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
            // HINSTANCE hGetProcIDDLL = LoadLibrary("d3d11_rendering_plugind.dll");
            HINSTANCE hGetProcIDDLL = LoadLibrary("opengl_rendering_plugind.dll");

            if (!hGetProcIDDLL)
            {
                std::cout << "could not load the dynamic library" << std::endl;
                return;
                // return EXIT_FAILURE;
            }

            // resolve function address here
            f_funci funci = (f_funci)GetProcAddress(hGetProcIDDLL, "Create");
            if (!funci)
            {
                std::cout << "could not locate the function" << std::endl;
                // return EXIT_FAILURE;
            }

            std::cout << "funci() returned " << funci() << std::endl;

            // RenderEngine* re = reinterpret_cast<RenderEngine*>(funci());
            // re->CreateRenderWindow();
#else
            auto re = Create();
            UNUSED_PARAMETER(re);

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