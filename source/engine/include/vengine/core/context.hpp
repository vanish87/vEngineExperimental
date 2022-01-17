#ifndef _VENGINE_CORE_CONTEXT_HPP
#define _VENGINE_CORE_CONTEXT_HPP

#pragma once

#include <VENGINE_API.h>

#include <engine.hpp>
#include <vengine/core/iruntime_module.hpp>
#include <vengine/core/configure.hpp>

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
                RenderEngine& GetRenderEngine()
                {
                    return *this->render_engine_ptr_;
                }

            public:
                void Init(...) override;
                void Deinit(...) override;
                void Update() override;

            private:
                Application* appInstance;
                std::unique_ptr<vEngine::Rendering::RenderEngine> render_engine_ptr_;

                void* lib_handle;
        };

    }  // namespace Core

}  // namespace vEngine

#endif /* _VENGINE_CORE_CONTEXT_HPP */
