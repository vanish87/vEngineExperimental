#ifndef _VENGINE_CORE_APPLICATION_MACOS_HPP
#define _VENGINE_CORE_APPLICATION_MACOS_HPP

#ifdef VENGINE_PLATFORM_APPLE
#include <vengine/core/application.hpp>
#include <apple/define.hpp>
#include <AppKit/AppKit.hpp>

namespace vEngine
{
    namespace Core
    {
        /// \brief A general example of user application
        class ApplicationMacOS : public Application, public NS::ApplicationDelegate
        {
            public:
            ApplicationMacOS(){}
            virtual ~ApplicationMacOS(){}
            virtual void applicationWillFinishLaunching(NS::Notification* pNotification) override{};
                virtual void applicationDidFinishLaunching(NS::Notification* pNotification) override;
            virtual bool applicationShouldTerminateAfterLastWindowClosed(NS::Application* pSender) override{};
                virtual void Run() override;
        };
    }  // namespace Core
}  // namespace vEngine
#endif

#endif /* _VENGINE_CORE_APPLICATION_MACOS_HPP */
