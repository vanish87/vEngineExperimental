
#include <vengine/core/context.hpp>
#include <engine.hpp>

#ifdef VENGINE_PLATFORM_WINDOWS
    #include <windows.h>
typedef int(__stdcall *f_funci)();
#else
extern "C" {
    vEngine::Core::RenderEngine* Create();
}
#endif
namespace vEngine
{
    namespace Core
    {
        Context::Context() {}
        Context::~Context() {}

        void Context::Setup()
        {
            // auto re = Create();
            // UNUSED_PARAMETER(re);

#ifdef VENGINE_PLATFORM_WINDOWS
            HINSTANCE hGetProcIDDLL =
                LoadLibrary("d3d11_rendering_plugind.dll");
            // HINSTANCE hGetProcIDDLL =
            // LoadLibrary("opengl_rendering_plugind.dll");

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
#else
            auto re = Create();
            UNUSED_PARAMETER(re);

#endif

            PRINT("testjJA");
        }
        void Context::RegisterAppInstance(ApplicationPtr app)
        {
            UNUSED_PARAMETER(app);
        }
    }  // namespace Core
}  // namespace vEngine