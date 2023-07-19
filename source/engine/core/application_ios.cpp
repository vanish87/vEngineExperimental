
#ifdef VENGINE_PLATFORM_APPLE
#include <vengine/core/application_ios.hpp>

namespace vEngine
{
    namespace Core
    {
        void ApplicationIOS::Run()
        {
            auto auto_release_pool = NS::AutoreleasePool::alloc()->init();
            UI::ApplicationMain(argc, argv, this);
            auto_release_pool->release();
        }

        bool ApplicationIOS::applicationDidFinishLaunching(UI::Application *pApp, NS::Value *options)
        {
            //Start another thread to run game loop
            this->RunAsync();
            return true;
        }
    }  // namespace Core
}  // namespace vEngine
#endif