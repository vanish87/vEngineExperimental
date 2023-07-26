#ifdef VENGINE_PLATFORM_APPLE
#include <vengine/core/window.hpp>
#include <apple/target_define.hpp>
#include <AppKit/AppKit.hpp>
#include <UIKit/UIKit.hpp>

namespace vEngine
{
    namespace Core
    {
        Window::Window(const WindowDescriptor& desc)
        {
            if(desc.wnd != nullptr)
            {
                this->wnd_ = desc.wnd;
            }
            else
            {
                #if defined(VENGINE_PLATFORM_TARGET_DARWIN)
                CGRect frame = (CGRect){ {0, 0}, {(float)desc.width, (float)desc.height} };
                auto window = NS::Window::alloc()->init(
                    frame,
                    NS::WindowStyleMaskClosable|NS::WindowStyleMaskTitled,
                    NS::BackingStoreBuffered,
                    false );
                window->setTitle( NS::String::string( desc.name.c_str(), NS::StringEncoding::UTF8StringEncoding ) );
                this->wnd_ = window;
                #elif defined(VENGINE_PLATFORM_TARGET_IOS)
                CGRect frame = UI::Screen::mainScreen()->bounds();
                this->wnd_ = UI::Window::alloc()->init(frame);
                #endif
            }
        }
        Window::~Window() {}
        void Window::Update() {}
    }  // namespace Core
}  // namespace vEngine

#endif
