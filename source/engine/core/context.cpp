
// DLL loader header
// #ifdef VENGINE_PLATFORM_WINDOWS
// #include <windows.h>
// #elif VENGINE_PLATFORM_UNIX
#ifdef VENGINE_PLATFORM_UNIX
    #include <dlfcn.h>
#endif

#include <vengine/core/context.hpp>
#include <vengine/data/json.hpp>
#include <vengine/core/window.hpp>
#include <vengine/core/application.hpp>
#include <vengine/core/game_object_factory.hpp>
#include <vengine/rendering/render_engine.hpp>

namespace vEngine
{
    namespace Core
    {
        typedef void (*HandleRenderEngine)(Rendering::RenderEngineUniquePtr& ptr);
        typedef void (*HandleGameObjectFactory)(GameObjectFactoryUniquePtr& ptr);

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
        void Context::Dispath(const IEvent& event)
        {
            VE_INFO("Event", event.ToString());
            for (const auto listener : this->event_listeners_)
            {
                if (auto l = listener.lock())
                {
                    l->OnEvent(event);
                }
            }
        }
        void Context::AddListenner(const IEventListenerSharedPtr listener)
        {
            this->event_listeners_.push_back(listener);
        }
        void Context::RemoveListener(const IEventListenerSharedPtr listener)
        {
            for (auto it = this->event_listeners_.begin(); it != this->event_listeners_.end();)
            {
                auto shared = it->lock();

                if (!shared)
                {
                    // Remove expired weak_ptrs
                    it = this->event_listeners_.erase(it);
                }
                else if (shared.get() == listener.get())
                {
                    // Found the matching element, remove it
                    it = this->event_listeners_.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }

        void Context::Init()
        {
            this->LoadDLL();

            auto config = this->configure_;
            auto path = config.resource_bin / config.context_name / "uuid.json";
            if (std::filesystem::exists(path)) FromJson(LoadJson(path), UUIDGenerator::GetInstance());

            auto graphics = this->configure_.graphics_configure;

            if (graphics.output == Output::Window)
            {
                WindowDescriptor desc;
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
            this->window_.reset();

            auto config = this->configure_;
            auto path = config.resource_bin / config.context_name / "uuid.json";
            SaveJson(ToJson(UUIDGenerator::GetInstance()), path);

            this->GetRenderEngine()->Deinit();
            this->render_engine_ptr_.reset();
            this->render_object_factory_ptr_.reset();
            this->custom_object_factory_ptr_.reset();
            // prt.reset() does same thing as this->ProcessRenderEngine("DestoryRenderEngine");

            this->FreeDLL();
        }
        void Context::Update()
        {
            if (this->CurrentWindow() != nullptr) this->CurrentWindow()->Update();
        }

        GameObjectFactoryUniquePtr& Context::GetRenderObjectFactory()
        {
            if (this->render_object_factory_ptr_ == nullptr)
            {
                #ifdef VENGINE_STATIC_LINK
                CreateGameObjectFactory(this->render_object_factory_ptr_);
                #elif VENGINE_DYNAMIC_LINK
                ProcessSharedFunction<GameObjectFactory, HandleGameObjectFactory>("CreateGameObjectFactory", this->render_plugin_dll_handle_, this->render_object_factory_ptr_);
                #endif
            }
            return this->render_object_factory_ptr_;
        }
        GameObjectFactoryUniquePtr& Context::GetCustomObjectFactory()
        {
            if (this->custom_object_factory_ptr_ == nullptr)
            {
                #ifdef VENGINE_STATIC_LINK
                CreateCustomGameObjectFactory(this->custom_object_factory_ptr_);
                #elif VENGINE_DYNAMIC_LINK
                ProcessSharedFunction<GameObjectFactory, HandleGameObjectFactory>("CreateCustomGameObjectFactory", this->custom_plugin_dll_handle_, this->custom_object_factory_ptr_);
                #endif
            }
            return this->custom_object_factory_ptr_;
        }

        Rendering::RenderEngineUniquePtr& Context::GetRenderEngine()
        {
            if (this->render_engine_ptr_ == nullptr)
            {
                #ifdef VENGINE_STATIC_LINK
                CreateRenderEngine(this->render_engine_ptr_);
                #elif VENGINE_DYNAMIC_LINK
                ProcessSharedFunction<Rendering::RenderEngine, HandleRenderEngine>("CreateRenderEngine", this->render_plugin_dll_handle_, this->render_engine_ptr_);
                #endif
            }
            return this->render_engine_ptr_;
        }

        void Context::LoadDLL()
        {
            #ifdef VENGINE_STATIC_LINK
            return;
            #else
            this->FreeDLL();

            const auto config = this->configure_;
            this->render_plugin_dll_handle_ = LoadLibrary(config.graphics_configure.render_plugin_name, config.library_bin);
            this->custom_plugin_dll_handle_ = LoadLibrary(config.custom_plugin_name, config.library_bin);
            #endif
        }
        void Context::FreeDLL()
        {
            if (this->render_plugin_dll_handle_ != nullptr)
            {
                FreeLibrary(this->render_plugin_dll_handle_);
                this->render_plugin_dll_handle_ = nullptr;
            }
            if (this->custom_plugin_dll_handle_ != nullptr)
            {
                FreeLibrary(this->custom_plugin_dll_handle_);
                this->custom_plugin_dll_handle_ = nullptr;
            }
        }

        // void Context::RegisterAppInstance(ApplicationSharedPtr app)
        // {
        //     this->app_ = app;
        // }
        // TODO Use Event/Observer Pattern to decouple application class
        // context could not having a app ptr
        // void Context::QuitApplication()
        // {
        //     // this->app_instance_ = app;
        //     auto app = this->app_.lock();
        //     VE_ASSERT_PTR_NOT_NULL(app);
        //     app->Quit();
        // }
        // Application& Context::AppInstance() const
        // {
        //     return *(this->app_instance_);
        // }

        void* Context::LoadLibrary(const std::string lib_name, const std::filesystem::path lib_bin)
        {
            #ifdef DEBUG
            auto dll_name = lib_name + VENGINE_SHARED_LIB_DEBUG_POSTFIX + VENGINE_SHARED_LIB_EXT;
            #else
            auto dll_name = lib_name + VENGINE_SHARED_LIB_EXT;
            #endif

            auto path = lib_bin / dll_name;
            if (!std::filesystem::exists(path)) return nullptr;

            #ifdef VENGINE_PLATFORM_WINDOWS
            auto handle = ::LoadLibrary(path.string().c_str());
            VE_ASSERT_PTR_NOT_NULL(handle, "could not load the dynamic library: " + dll_name);

            #elif VENGINE_PLATFORM_UNIX
            dlerror();
            auto handle = dlopen(path.string().c_str(), RTLD_LAZY);
            VE_ASSERT_PTR_NOT_NULL(handle, "Cannot open library: ", std::string(dlerror()));
            #else
            auto handle = nullptr;
            #endif
            return handle;
        }

        void Context::FreeLibrary(void* handle)
        {
            #ifdef VENGINE_PLATFORM_WINDOWS
            if (handle != nullptr) ::FreeLibrary(reinterpret_cast<HMODULE>(handle));
            #elif VENGINE_PLATFORM_UNIX
            dlclose(handle);
            #endif
        }

        template <typename T, typename F>
        void Context::ProcessSharedFunction(const std::string func_name, void* handle, std::unique_ptr<T>& ptr)
        {
            F function;
            #ifdef VENGINE_PLATFORM_WINDOWS
            function = reinterpret_cast<F>(::GetProcAddress(reinterpret_cast<HMODULE>(handle), func_name.c_str()));
            #elif VENGINE_PLATFORM_UNIX
            // reset errors
            dlerror();
            function = reinterpret_cast<F>(dlsym(handle, func_name.c_str()));
            auto dlsym_error = dlerror();
            if (dlsym_error)
            {
                VE_ASSERT(false, "Cannot load symbol ", func_name, dlsym_error);
            }
            #endif
            VE_ASSERT_PTR_NOT_NULL(function, "could not locate the function " + func_name);

            if (function != nullptr)
            {
                function(ptr);
            }
        }
    }  // namespace Core
}  // namespace vEngine
