#ifndef _VENGINE_CORE_CONTEXT_HPP
#define _VENGINE_CORE_CONTEXT_HPP

#pragma once

#include <unordered_map>

#include <engine.hpp>
#include <vengine/core/game_object.hpp>
#include <vengine/data/meta.hpp>
#include <vengine/core/configure.hpp>
#include <vengine/core/iruntime_module.hpp>

namespace vEngine
{
    namespace Core
    {
        class VENGINE_API Context : public IRuntimeModule
        {
                SINGLETON_CLASS(Context)

            public:
                /// \brief Load all factories that create resource
                ///
                void ConfigureWith(const Configure& configure);
                const Configure CurrentConfigure() const;

                void RegisterAppInstance(Application* app);
                Application& AppInstance() const;
                // RenderFactory& RenderFactoty();

            public:
                Rendering::RenderEngine & GetRenderEngine();

            public:
                void Init() override;
                void Deinit() override;
                void Update() override;

            private:
                void LoadDll();
                void FreeDll();
                void LoadRuntimeObjects();
                void SaveRuntimeObjects();
                GameObjectSharedPtr Find(const UUID& uuid);
                void Register(const GameObjectSharedPtr& go);

            private:
                Configure configure_;
                Application* app_instance_;

                void* render_plugin_dll_handle_;
                Rendering::RenderEngineUniquePtr render_engine_ptr_;

                std::unordered_map<UUID, GameObjectSharedPtr> runtime_game_objects_;

            public:
                constexpr static auto properties()
                {
                    return std::make_tuple(property("context_objects", &Context::runtime_game_objects_));
                }
        };

        void* LoadLibrary(const std::string lib_name);
        void  FreeLibrary(void* handle);
        template <typename T>
        void ProcessSharedFunction(const std::string func_name, void* handle, std::unique_ptr<T>& ptr);

    }  // namespace Core

}  // namespace vEngine

#endif /* _VENGINE_CORE_CONTEXT_HPP */
