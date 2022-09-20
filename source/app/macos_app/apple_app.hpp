#ifndef _APP_MACOS_APP_APPLE_APP_HPP
#define _APP_MACOS_APP_APPLE_APP_HPP

#include <engine.hpp>
#include <vengine/core/application.hpp>
#include <version.hpp>

using namespace vEngine::Core;

/// Namespace for example applications
namespace AppleApp
{
    /// \brief A general example of user application
    class ExampleApp : public Application
    {
        private:
            /// \brief user function for create
            ///
            void OnCreate() override
            {
                PRINT("User Create");
            }
            /// \brief user function for update
            ///
            /// Will be call at const seconds
            /// vEngine::TIME_PER_UPDATE
            void OnUpdate() override {}
            /// \brief user function for destroy
            void OnDestory() override
            {
                PRINT("User Destory");
            }
    };
}  // namespace AppleApp

#endif /* _APP_MACOS_APP_APPLE_APP_HPP */
