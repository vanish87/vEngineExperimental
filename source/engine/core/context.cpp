
// DLL loader header
// #ifdef VENGINE_PLATFORM_WINDOWS
// #include <windows.h>
// #elif VENGINE_PLATFORM_UNIX
#if VENGINE_PLATFORM_UNIX
    #include <dlfcn.h>
#endif

#include <vengine/core/context.hpp>
// #include <vengine/core/application.hpp>
#include <vengine/rendering/render_engine.hpp>
#include <vengine/core/window.hpp>
#include <vengine/core/application.hpp>
// #include <vengine/core/resource_loader.hpp>

// #include <vengine/data/meta.hpp>
// #include <vengine/data/json.hpp>
// #include <fstream>

namespace vEngine
{
    namespace Core
    {
        typedef void (*HandleRenderEngine)(Rendering::RenderEngineUniquePtr& ptr);

        Context::Context() {}
        Context::~Context() {}
        Configure Context::CurrentConfigure() const
        {
            return this->configure_;
        }

        void Context::SetConfigure(const Configure& configure)
        {
            this->configure_ = configure;
        }

        WindowSharedPtr Context::CurrentWindow() const
        {
            return this->window_;
        }

        void Context::Init()
        {
            this->LoadDll();

            auto graphics = this->configure_.graphics_configure;

            if (graphics.output == Output::Window)
            {
                WindowDescription desc;
                desc.name = this->configure_.app_name;
                desc.width = graphics.width;
                desc.height = graphics.height;
                desc.wnd = graphics.wnd;
                this->window_ = std::make_shared<Window>(desc);
            }

            this->GetRenderEngine()->Init();
        }
        void Context::Deinit()
        {
            this->Clear();

            this->window_.reset();

            this->GetRenderEngine()->Deinit();
            this->render_engine_ptr_.reset();
            // prt.reset() does same thing as this->ProcessRenderEngine("DestoryRenderEngine");

            this->FreeDll();
        }
        void Context::Update()
        {
            if (this->CurrentWindow() != nullptr) this->CurrentWindow()->Update();
        }

        Rendering::RenderEngineUniquePtr& Context::GetRenderEngine()
        {
            if (this->render_engine_ptr_ == nullptr)
            {
                #ifdef VENGINE_PLATFORM_APPLE_STATIC
                CreateRenderEngine(this->render_engine_ptr_);
                #else
                ProcessSharedFunction<Rendering::RenderEngine, HandleRenderEngine>("CreateRenderEngine", this->render_plugin_dll_handle_, this->render_engine_ptr_);
                #endif
            }
            return this->render_engine_ptr_;
        }

        void Context::LoadDll()
        {
            #ifdef VENGINE_PLATFORM_APPLE_STATIC
            return;
            #endif
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

        // GameObjectSharedPtr Context::Find(const UUID& uuid)
        // {
        //     if (this->runtime_game_objects_.find(uuid) != this->runtime_game_objects_.end())
        //     {
        //         return this->runtime_game_objects_[uuid];
        //     }
        //     return nullptr;
        // }
        // void Context::Register(const GameObjectSharedPtr& go)
        // {
        //     // UNUSED_PARAMETER(go);
        //     const auto& uuid = go->description_.uuid;
        //     CHECK_ASSERT(this->runtime_game_objects_.find(uuid) == this->runtime_game_objects_.end());
        //     this->runtime_game_objects_[uuid] = go;
        // }

        void Context::RegisterAppInstance(ApplicationSharedPtr app)
        {
            this->app_ = app;
        }
        void Context::QuitApplication()
        {
            // this->app_instance_ = app;
            auto app = this->app_.lock();
            CHECK_ASSERT_NOT_NULL(app);
            app->Quit();
        }
        // Application& Context::AppInstance() const
        // {
        //     return *(this->app_instance_);
        // }

        void* LoadLibrary(const std::string lib_name)
        {
            #ifdef DEBUG
            auto dll_name = VENGINE_SHARED_LIB_PREFIX + lib_name + VENGINE_SHARED_LIB_DEBUG_POSTFIX + VENGINE_SHARED_LIB_EXT;
            #else
            auto dll_name = VENGINE_SHARED_LIB_PREFIX + lib_name + VENGINE_SHARED_LIB_EXT;
            #endif

            #ifdef VENGINE_PLATFORM_WINDOWS
            auto handle = ::LoadLibrary(dll_name.c_str());
            if (!handle)
            {
                PRINT_AND_BREAK("could not load the dynamic library");
            }
            #elif VENGINE_PLATFORM_UNIX
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
            #elif VENGINE_PLATFORM_UNIX
            dlclose(handle);
            #endif
        }

        template <typename T, typename F>
        void ProcessSharedFunction(const std::string func_name, void* handle, std::unique_ptr<T>& ptr)
        {
            #ifdef VENGINE_PLATFORM_WINDOWS
            auto function = reinterpret_cast<F>(::GetProcAddress(reinterpret_cast<HMODULE>(handle), func_name.c_str()));
            #elif VENGINE_PLATFORM_UNIX
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
                PRINT_AND_BREAK("could not locate the function " << func_name);
            }
        }
    }  // namespace Core
}  // namespace vEngine
