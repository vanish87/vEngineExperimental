#ifndef _VENGINE_CORE_APPLICATION_IOS_HPP
#define _VENGINE_CORE_APPLICATION_IOS_HPP

#ifdef VENGINE_PLATFORM_APPLE
#include <vengine/core/application.hpp>

namespace vEngine
{
    namespace Core
    {
        /// \brief A general example of user application
        class ApplicationIOS : public Application, public UI::ApplicationDelegate
        {
            public:
                bool applicationDidFinishLaunching(UI::Application *pApp, NS::Value *options) override;
                void applicationWillTerminate(UI::Application *pApp) override;
        };
    }  // namespace Core
}  // namespace vEngine
#endif


#endif /* _VENGINE_CORE_APPLICATION_IOS_HPP */
