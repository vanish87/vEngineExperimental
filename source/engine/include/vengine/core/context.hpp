/// \file context.hpp
/// \brief Head file for Context
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_CONTEXT_HPP
#define _VENGINE_CORE_CONTEXT_HPP

#pragma once

#include <engine.hpp>
#include <vengine/core/configure.hpp>

namespace vEngine
{
    namespace Core
    {
        class VENGINE_API Context
        {
                // friend class GameObjectFactory;
                SINGLETON_CLASS(Context)

            public:
                /// \brief Load all factories that create resource
                ///
                Configure CurrentConfigure() const;

                void RegisterAppInstance(ApplicationSharedPtr app);
                void QuitApplication();

                WindowSharedPtr CurrentWindow() const;
                // Application& AppInstance() const;
                // RenderFactory& RenderFactoty();

            public:
                Rendering::RenderEngineUniquePtr& GetRenderEngine();
                GameObjectFactoryUniquePtr& GetRenderObjectFactory();

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
                ApplicationWeakPtr app_;
                WindowSharedPtr window_;

                void* custom_plugin_dll_handle_;
                GameObjectFactoryUniquePtr custom_object_factory_ptr_;

                void* render_plugin_dll_handle_;
                GameObjectFactoryUniquePtr render_object_factory_ptr_;
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
