#ifndef _VENGINE_CORE_CONTEXT_HPP
#define _VENGINE_CORE_CONTEXT_HPP

#pragma once

#include <CORE_API.h>

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

                void RegisterAppInstance(ApplicationPtr app);
                // RenderFactory& RenderFactoty();

            public:
                bool ShouldQuit();
                void SetQuit(bool value);

            private:
                bool quit_;
                ApplicationPtr appInstance;
        };

    }  // namespace Core

}  // namespace vEngine

#endif /* _VENGINE_CORE_CONTEXT_HPP */
