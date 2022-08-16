
#ifdef VENGINE_PLATFORM_WINDOWS
    #include <windows.h>
#elif VENGINE_PLATFORM_UNIX
    #include <dlfcn.h>
#endif

#include <engine.hpp>
#include <vengine/core/application.hpp>
#include <vengine/core/context.hpp>
#include <vengine/rendering/render_engine.hpp>
#include <vengine/core/resource_loader.hpp>

#include <vengine/data/meta.hpp>
#include <vengine/data/json.hpp>
#include <fstream>

namespace vEngine
{
    namespace Core
    {
        typedef void (*HandleRenderEngine)(Rendering::RenderEngineUniquePtr& ptr);

        Context::Context() : app_instance_{nullptr} {}
        Context::~Context() {}
        const Configure Context::CurrentConfigure() const
        {
            return this->configure_;
        }

        /// Load Dll
        /// Create Redering
        void Context::Init(const Configure& configure)
        {
            this->configure_ = configure;
            this->LoadDll();

            ResourceLoader::GetInstance().Init();

            this->LoadRuntimeObjects();
        }

        void Context::Deinit()
        {
            this->SaveRuntimeObjects();

            ResourceLoader::GetInstance().Deinit();
            // prt.reset() does same thing as this->ProcessRenderEngine("DestoryRenderEngine");
            this->render_engine_ptr_.reset();

            // nlohmann::json j;
            // ToJson(j, this->runtime_game_objects_);

            this->FreeDll();
        }
        void Context::Update() {}

        Rendering::RenderEngine& Context::GetRenderEngine()
        {
            if (this->render_engine_ptr_ == nullptr)
            {
                #ifdef VENGINE_PLATFORM_APPLE_STATIC
                CreateRenderEngine(this->render_engine_ptr_);
                #else
                ProcessSharedFunction<Rendering::RenderEngine, HandleRenderEngine>("CreateRenderEngine", this->render_plugin_dll_handle_, this->render_engine_ptr_);
                #endif
            }
            return *this->render_engine_ptr_;
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

        void Context::LoadRuntimeObjects() 
        {
            auto config = this->CurrentConfigure();
            auto context_path =config.resource_bin / config.context_name;
            auto uuid_path = context_path / "uuid.json";
            auto j = ParseJson(uuid_path);

            FromJson(j, UUIDGenerator::GetInstance());

            std::unordered_map<uint64_t, nlohmann::json> json_map;

            for(const auto& file : std::filesystem::directory_iterator(context_path))
            {
                auto name = file.path().filename().string();
                if (name == "uuid") continue;
                if(file.is_regular_file())
                {
                    auto uuid = std::stoi(name.substr(0, name.find('_')));
                    json_map[uuid] = ParseJson(file.path());
                }
            }
            for(auto& json : json_map)
            {
                GameObjectSharedPtr go;
                FromJson(json.second, go);
                this->runtime_game_objects_[go->description_.uuid] = go;
            }

        }
        void Context::SaveRuntimeObjects() 
        {
            auto config = this->CurrentConfigure();
            auto context_path =config.resource_bin / config.context_name;
            if (!std::filesystem::exists(context_path)) std::filesystem::create_directory(context_path);

            std::string illegal = ":\"\'<>%$*&+ ";

            auto uuid = ToJson(UUIDGenerator::GetInstance());
            auto uuid_path = context_path / "uuid.json";
            std::ofstream uuid_file(uuid_path.string());
            uuid_file << std::setw(2) << uuid << std::endl;
            uuid_file.flush();
            uuid_file.close();

            for(const auto& go : this->runtime_game_objects_)
            {
                nlohmann::json j;
                auto name = go.second->description_.name;
                auto type = go.second->description_.type;

                auto file_name = std::to_string(go.first.AsUint()) + "_" + name + "_" + type + ".json";
                for(auto c : illegal)
                {
                    std::replace(file_name.begin(), file_name.end(), c, '_');
                }

                auto output = context_path / file_name;
                j = ToJson(go.second, false);
                PRINT("Save to " << output.string());
                std::ofstream outfile(output.string());
                outfile << std::setw(2) << j << std::endl;
                outfile.flush();
                outfile.close();

            }
            this->runtime_game_objects_.clear();
        }
        GameObjectSharedPtr Context::Find(const UUID& uuid)
        {
            if (this->runtime_game_objects_.find(uuid) != this->runtime_game_objects_.end())
            {
                return this->runtime_game_objects_[uuid];
            }
            else
            {}
            return nullptr;
        }
        void Context::Register(const GameObjectSharedPtr& go)
        {
            // UNUSED_PARAMETER(go);
            const auto& uuid = go->description_.uuid;
            CHECK_ASSERT(this->runtime_game_objects_.find(uuid) == this->runtime_game_objects_.end());
            this->runtime_game_objects_[uuid] = go;
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
            auto dll_name = VENGINE_SHADRED_LIB_PREFIX + lib_name + VENGINE_SHADRED_LIB_DEBUG_POSTFIX + VENGINE_SHADRED_LIB_EXT;

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
                PRINT_AND_BREAK("could not locate the function CreateRenderEngine");
            }
        }
    }  // namespace Core
}  // namespace vEngine
