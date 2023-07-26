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
                SINGLETON_CLASS(Context)

            public:
                /// \brief Load all factories that create resource
                ///
                Configure CurrentConfigure() const;

                void RegisterAppInstance(ApplicationSharedPtr app);
                void QuitApplication();

                WindowSharedPtr CurrentWindow() const;
                // Application& AppInstance() const;

            public:
                Rendering::RenderEngineUniquePtr& GetRenderEngine();
                GameObjectFactoryUniquePtr& GetRenderObjectFactory();
                GameObjectFactoryUniquePtr& GetCustomObjectFactory();

            public:
                void SetConfigure(const Configure& configure);
                void Init();
                void Deinit();
                void Update();

            private:
                void LoadDLL();
                void FreeDLL();

                static void* LoadLibrary(const std::string lib_name,const std::filesystem:: path lib_bin);
                static void FreeLibrary(void* handle);
                template <typename T, typename F>
                static void ProcessSharedFunction(const std::string func_name, void* handle, std::unique_ptr<T>& ptr);

            private:
                Configure configure_;
                ApplicationWeakPtr app_;
                WindowSharedPtr window_;

                void* custom_plugin_dll_handle_;
                GameObjectFactoryUniquePtr custom_object_factory_ptr_;

                void* render_plugin_dll_handle_;
                GameObjectFactoryUniquePtr render_object_factory_ptr_;
                Rendering::RenderEngineUniquePtr render_engine_ptr_;
        };


    }  // namespace Core

}  // namespace vEngine

#endif /* _VENGINE_CORE_CONTEXT_HPP */
