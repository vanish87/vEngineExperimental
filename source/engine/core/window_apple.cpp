#ifdef VENGINE_PLATFORM_APPLE
#include <vengine/core/window.hpp>
#include <apple/define.hpp>
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
                #ifdef APPLE_PLATFORM_TARGET_DARWIN
                    CGRect frame = (CGRect){ {100.0, 100.0}, {512.0, 512.0} };
                    this->wnd_ = NS::Window::alloc()->init(frame, NS::WindowStyleMaskClosable | NS::WindowStyleMaskTitled, NS::BackingStoreBuffered, false);
                #endif
            }
        }
        Window::~Window() {}
        void Window::Update() {}
    }  // namespace Core
}  // namespace vEngine

#endif