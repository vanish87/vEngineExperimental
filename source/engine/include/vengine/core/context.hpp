#ifndef _VENGINE_CORE_CONTEXT_HPP
#define _VENGINE_CORE_CONTEXT_HPP

#pragma once

#include <VENGINE_API.h>

#include <engine.hpp>
#include <vengine/core/configure.hpp>
#include <vengine/core/iruntime_module.hpp>

namespace vEngine
{
    namespace Core
    {
        using namespace vEngine::Rendering;

        class Context : public IRuntimeModule
        {
                SINGLETON_CLASS(Context)

            public:
                /// \brief Load all factories that create resource
                ///
                void ConfigureWith(const Configure& configure);

                void RegisterAppInstance(Application* app);
                Application& AppInstance() const;
                // RenderFactory& RenderFactoty();

            public:
                RenderEngine& GetRenderEngine();

            public:
                void Init(...) override;
                void Deinit(...) override;
                void Update() override;

            private:
                void LoadDll();
                void FreeDll();

                void ProcessRenderEngine(const std::string func_name);

            private:
                Configure configure_;
                Application* app_instance_;

                void* render_plugin_dll_handle_;
                std::unique_ptr<RenderEngine> render_engine_ptr_;
        };

    }  // namespace Core

}  // namespace vEngine

#endif /* _VENGINE_CORE_CONTEXT_HPP */
