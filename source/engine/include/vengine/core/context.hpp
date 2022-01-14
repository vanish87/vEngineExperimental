#ifndef _VENGINE_CORE_CONTEXT_HPP
#define _VENGINE_CORE_CONTEXT_HPP

#pragma once

#include <VENGINE_API.h>

#include <engine.hpp>

namespace vEngine
{
    namespace Core
    {
        class Context
        {
            SINGLETON_CLASS(Context)

            public:
                /// \brief Load all factories that create resource
                ///
                void Setup();

                void RegisterAppInstance(Application* app);
                Application& AppInstance() const;
                // RenderFactory& RenderFactoty();

            private:
                Application* appInstance;
                std::unique_ptr<vEngine::Rendering::RenderEngine> render_engine_ptr_;
        };

    }  // namespace Core

}  // namespace vEngine

#endif /* _VENGINE_CORE_CONTEXT_HPP */
