#ifndef _VENGINE_CORE_IAPPLICATION_HPP
#define _VENGINE_CORE_IAPPLICATION_HPP

#pragma once
#include <VENGINE_API.h>

#include <vengine/core/iruntime_module.hpp>

namespace vEngine
{
    namespace Core
    {
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        Interface VENGINE_API IApplication : public IRuntimeModule
        {
        public:
            virtual void Run() = 0;

            virtual void Init(...) = 0;
            virtual void Deinit(...) = 0;
            virtual void Update() = 0;

            virtual void Quit(bool quit) = 0;

        protected:
            WindowPtr window_;

        private:
            virtual void OnCreate() = 0;
            virtual void OnUpdate() = 0;
            virtual void OnDestory() = 0;

            virtual void SetupWindow() = 0;
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_IAPPLICATION_HPP */
