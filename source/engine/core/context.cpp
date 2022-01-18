
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

        void Context::Init(...) {}
        void Context::Deinit(...)
        {
            //prt.reset() does same thing
            // this->ProcessRenderEngine("DestoryRenderEngine");
            this->render_engine_ptr_.reset();
            this->FreeDll();
        }
        void Context::Update() {}

        void Context::ProcessRenderEngine(const std::string func_name)
        {
            #ifdef VENGINE_PLATFORM_WINDOWS
            auto function = reinterpret_cast<HandleRenderEngine>(::GetProcAddress(reinterpret_cast<HMODULE>(this->render_plugin_dll_handle_), func_name.c_str()));
            #elif VENGINE_PLATFORM_LINUX

            // reset errors
            dlerror();
            auto function = reinterpret_cast<HandleRenderEngine>(dlsym(this->render_plugin_dll_handle_, func_name.c_str()));
            auto dlsym_error = dlerror();
            if (dlsym_error)
            {
                PRINT_AND_BREAK("Cannot load symbol " + func_name + dlsym_error);
            }
            #endif
            if (function != nullptr)
            {
                function(this->render_engine_ptr_);
                if (this->render_engine_ptr_ != nullptr)
                {
                    this->render_engine_ptr_->PrintInfo();
                }
            }
            else
            {
                PRINT_AND_BREAK("could not locate the function CreateRenderEngine");
            }
        }

        RenderEngine& Context::GetRenderEngine()
        {
            if (this->render_engine_ptr_ == nullptr)
            {
                this->ProcessRenderEngine("CreateRenderEngine");
            }
            return *this->render_engine_ptr_;
        }

        void Context::LoadDll()
        {
            this->FreeDll();

            auto render_dll_name = this->configure_.graphics_configure.render_plugin_name;

            #ifdef VENGINE_PLATFORM_WINDOWS
            render_dll_name += "_rendering_plugind.dll";
            this->render_plugin_dll_handle_ = ::LoadLibrary(render_dll_name.c_str());
            // auto hGetProcIDDLL = ::LoadLibrary("opengl_rendering_plugind.dll");

            if (!this->render_plugin_dll_handle_)
            {
                PRINT_AND_BREAK("could not load the dynamic library");
            }
            #elif VENGINE_PLATFORM_LINUX
            render_dll_name = "./lib" + render_dll_name + "_rendering_plugind.dylib";
            // render_dll_name = "./lib" + render_dll_name + "_rendering_plugind.so";

            dlerror();
            this->render_plugin_dll_handle_ = dlopen(render_dll_name.c_str(), RTLD_LAZY);
            if (!this->render_plugin_dll_handle_)
            {
                auto dlsym_error = dlerror();
                PRINT_AND_BREAK("Cannot open library: " + std::string(dlsym_error));
            }
            #endif
        }
        void Context::FreeDll()
        {
            if (this->render_plugin_dll_handle_ != nullptr)
            {
                #ifdef VENGINE_PLATFORM_WINDOWS
                ::FreeLibrary(reinterpret_cast<HMODULE>(this->render_plugin_dll_handle_));
                #elif VENGINE_PLATFORM_LINUX
                dlclose(this->render_plugin_dll_handle_);
                #endif
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

        void Context::RegisterAppInstance(Application* app)
        {
            // UNUSED_PARAMETER(app);
            this->app_instance_ = app;
        }
        Application& Context::AppInstance() const
        {
            return *(this->app_instance_);
        }
    }  // namespace Core
}  // namespace vEngine