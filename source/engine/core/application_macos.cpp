
#ifdef VENGINE_PLATFORM_APPLE
#include <vengine/core/application_macos.hpp>

namespace vEngine
{
    namespace Core
    {
        void ApplicationMacOS::Run()
        {
            auto auto_release_pool = NS::AutoreleasePool::alloc()->init();

            auto app = NS::Application::sharedApplication();
            app->setDelegate(this);
            app->run();

            auto_release_pool->release();
        }
        void ApplicationMacOS::applicationDidFinishLaunching( NS::Notification* pNotification )
        {
            this->RunAsync();
        }
    }
}

#endif
