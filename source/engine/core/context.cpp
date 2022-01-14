
#ifdef VENGINE_PLATFORM_WINDOWS
    #include <windows.h>
#elif  VENGINE_PLATFORM_LINUX
    #include <dlfcn.h>
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
            // this->render_engine_ptr_->CreateRenderWindow();

            ::FreeLibrary(hGetProcIDDLL);

#elif VENGINE_PLATFORM_LINUX

            auto handle = dlopen("./libopengl_rendering_plugin.so", RTLD_LAZY);
            if (!handle)
            {
                std::cerr << "Cannot open library: " << dlerror() << '\n';
                return;
            }

            // load the symbol
            std::cout << "Loading symbol hello...\n";

            // reset errors
            dlerror();
            auto func = (CreateRenderEngine)dlsym(handle, "CreateRenderEngine");
            const char* dlsym_error = dlerror();
            if (dlsym_error)
            {
                std::cerr << "Cannot load symbol 'hello': " << dlsym_error << '\n';
                dlclose(handle);
                return;
            }

            // use it to do the calculation
            std::cout << "Calling hello...\n";
            func(this->render_engine_ptr_);
            this->render_engine_ptr_->PrintInfo();
            // this->render_engine_ptr_->CreateRenderWindow();

            // close the library
            std::cout << "Closing library...\n";
            dlclose(handle);
#endif

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