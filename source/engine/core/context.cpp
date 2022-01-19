
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
    namespace Core
    {
        typedef void (*HandleRenderEngine)(std::unique_ptr<RenderEngine>& ptr);

        Context::Context() : app_instance_{nullptr} {}
        Context::~Context() {}

        void Context::Init() {}
        void Context::Deinit()
        {
            //prt.reset() does same thing as this->ProcessRenderEngine("DestoryRenderEngine");
            this->render_engine_ptr_.reset();

            this->FreeDll();
        }
        void Context::Update() {}

        RenderEngine& Context::GetRenderEngine()
        {
            if (this->render_engine_ptr_ == nullptr)
            {
                ProcessSharedFunction("CreateRenderEngine", this->render_plugin_dll_handle_, this->render_engine_ptr_);
            }
            return *this->render_engine_ptr_;
        }

        void Context::LoadDll()
        {
            this->FreeDll();

            auto render_dll_name = this->configure_.graphics_configure.render_plugin_name;
            this->render_plugin_dll_handle_ = LoadLibrary(render_dll_name);

        }
        void Context::FreeDll()
        {
            if (this->render_plugin_dll_handle_ != nullptr)
            {
                FreeLibrary(this->render_plugin_dll_handle_);
                this->render_plugin_dll_handle_ = nullptr;
            }
        }

        /// Load Dll
        /// Create Redering
        void Context::ConfigureWith(const Configure& configure)
        {
            this->configure_ = configure;
            this->LoadDll();
        }

        const Configure Context::CurrentConfigure() const
        {
            return this->configure_;
        }

        void Context::RegisterAppInstance(Application* app)
        {
            this->app_instance_ = app;
        }
        Application& Context::AppInstance() const
        {
            return *(this->app_instance_);
        }

        void* LoadLibrary(const std::string lib_name)
        {
            std::string dll_name = VENGINE_SHADRED_LIB_PREFIX + lib_name + VENGINE_SHADRED_LIB_DEBUG_POSTFIX + VENGINE_SHADRED_LIB_EXT;

            #ifdef VENGINE_PLATFORM_WINDOWS
            auto handle = ::LoadLibrary(dll_name.c_str());
            if (!handle)
            {
                PRINT_AND_BREAK("could not load the dynamic library");
            }
            #elif VENGINE_PLATFORM_LINUX
            dlerror();
            auto handle = dlopen(dll_name.c_str(), RTLD_LAZY);
            if (!handle)
            {
                PRINT_AND_BREAK("Cannot open library: " + std::string(dlerror()));
            }
            #endif

            return handle;
        }

        void FreeLibrary(void* handle)
        {
            #ifdef VENGINE_PLATFORM_WINDOWS
            ::FreeLibrary(reinterpret_cast<HMODULE>(handle));
            #elif VENGINE_PLATFORM_LINUX
            dlclose(handle);
            #endif
        }

        template <typename T>
        void ProcessSharedFunction(const std::string func_name, void* handle, std::unique_ptr<T>& ptr)
        {
            #ifdef VENGINE_PLATFORM_WINDOWS
            auto function = reinterpret_cast<HandleRenderEngine>(::GetProcAddress(reinterpret_cast<HMODULE>(handle), func_name.c_str()));
            #elif VENGINE_PLATFORM_LINUX
            // reset errors
            dlerror();
            auto function = reinterpret_cast<HandleRenderEngine>(dlsym(handle, func_name.c_str()));
            auto dlsym_error = dlerror();
            if (dlsym_error)
            {
                PRINT_AND_BREAK("Cannot load symbol " + func_name + dlsym_error);
            }
            #endif
            if (function != nullptr)
            {
                function(ptr);
            }
            else
            {
                PRINT_AND_BREAK("could not locate the function CreateRenderEngine");
            }
        }
    }  // namespace Core
}  // namespace vEngine