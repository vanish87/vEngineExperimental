#ifndef _VENGINE_CORE_CONTEXT_HPP
#define _VENGINE_CORE_CONTEXT_HPP

#pragma once

// #include <unordered_map>

#include <engine.hpp>
// #include <vengine/core/game_object.hpp>
// #include <vengine/data/meta.hpp>
#include <vengine/core/configure.hpp>
#include <vengine/rendering/render_engine.hpp>
// #include <vengine/core/iruntime_module.hpp>

namespace vEngine
{
    namespace Core
    {
        class VENGINE_API Context
        {
                friend class GameObjectFactory;
                SINGLETON_CLASS(Context)

            public:
                template <GameObjectType Type>
                GameObjectSharedPtr Create()
                {
                    if constexpr (Type == GameObjectType::Mesh) return std::make_shared<Mesh>();
                    // return nullptr;
                }

            public:
                /// \brief Load all factories that create resource
                ///
                const Configure CurrentConfigure() const;

                void RegisterAppInstance(Application* app);
                void QuitApplication();

                WindowSharedPtr CurrentWindow() const;
                // Application& AppInstance() const;
                // RenderFactory& RenderFactoty();

            public:
                Rendering::RenderEngine& GetRenderEngine();

            public:
                void SetConfigure(const Configure& configure);
                void Init();
                void Deinit();
                void Update();

                void Clear()
                {
                    // this->runtime_game_objects_.clear();
                }

            private:
                void LoadDll();
                void FreeDll();
                // GameObjectSharedPtr Find(const UUID& uuid);
                // void Register(const GameObjectSharedPtr& go);

            private:
                Configure configure_;
                Application* app_instance_;
                WindowSharedPtr window_;

                void* render_plugin_dll_handle_;
                Rendering::RenderEngineUniquePtr render_engine_ptr_;

                // std::unordered_map<UUID, GameObjectSharedPtr> runtime_game_objects_;

            public:
                // constexpr static auto properties()
                // {
                //     return std::make_tuple(
                //         property("context_objects", &Context::runtime_game_objects_));
                // }
        };

        void* LoadLibrary(const std::string lib_name);
        void FreeLibrary(void* handle);
        template <typename T, typename F>
        void ProcessSharedFunction(const std::string func_name, void* handle, std::unique_ptr<T>& ptr);

    }  // namespace Core

}  // namespace vEngine

#endif /* _VENGINE_CORE_CONTEXT_HPP */
