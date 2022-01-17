
#ifdef VENGINE_PLATFORM_WINDOWS
    #include <windows.h>
#elif VENGINE_PLATFORM_LINUX
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

        void Context::Init(...) {}
        void Context::Deinit(...)
        {
            this->render_engine_ptr_.reset();
            
#ifdef VENGINE_PLATFORM_WINDOWS
            ::FreeLibrary(reinterpret_cast<HMODULE>(this->lib_handle));
#elif VENGINE_PLATFORM_LINUX
            dlclose(this->lib_handle);
#endif

        }
        void Context::Update() {}

        /// Load Dll
        /// Create Redering
        void Context::ConfigureWith(const Configure& configure)
        {
            auto dllName = configure.graphics_configure.render_plugin_name;

#ifdef VENGINE_PLATFORM_WINDOWS
            dllName += "_rendering_plugind.dll";
            this->lib_handle = ::LoadLibrary(dllName.c_str());
            // auto hGetProcIDDLL = ::LoadLibrary("opengl_rendering_plugind.dll");

            if (!this->lib_handle)
            {
                std::cout << "could not load the dynamic library" << std::endl;
                return;
                // return EXIT_FAILURE;
            }

            // resolve function address here
            auto create_function = reinterpret_cast<CreateRenderEngine>(::GetProcAddress(reinterpret_cast<HMODULE>(this->lib_handle), "CreateRenderEngine"));
            if (!create_function)
            {
                std::cout << "could not locate the function" << std::endl;
                ::FreeLibrary(reinterpret_cast<HMODULE>(this->lib_handle));
                return;
            }

#elif VENGINE_PLATFORM_LINUX

            dllName = "./lib" + dllName + "_rendering_plugind.dylib";
            // dllName = "./lib" + dllName + "_rendering_plugind.so";

            this->lib_handle = dlopen(dllName.c_str(), RTLD_LAZY);
            if (!this->lib_handle)
            {
                std::cerr << "Cannot open library: " << dlerror() << '\n';
                return;
            }

            // reset errors
            dlerror();
            auto create_function = (CreateRenderEngine)dlsym(this->lib_handle, "CreateRenderEngine");
            const char* dlsym_error = dlerror();
            if (dlsym_error)
            {
                std::cerr << "Cannot load symbol 'hello': " << dlsym_error << '\n';
                dlclose(this->lib_handle);
                return;
            }

#endif

            create_function(this->render_engine_ptr_);
            CHECK_ASSERT_NOT_NULL(this->render_engine_ptr_);
            this->render_engine_ptr_->PrintInfo();
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