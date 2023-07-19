#ifndef _VENGINE_RENDERING_METAL_MTK_VIEW_DELEGATE_HPP
#define _VENGINE_RENDERING_METAL_MTK_VIEW_DELEGATE_HPP

#include <Foundation/Foundation.hpp>
#include <QuartzCore/QuartzCore.hpp>
#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>

namespace vEngine
{
    namespace Rendering
    {
        class MetalMTKViewDelegate : public MTK::ViewDelegate
        {
            public:
                MetalMTKViewDelegate(MTL::Device* pDevice);
                virtual ~MetalMTKViewDelegate() override;
                virtual void drawInMTKView(MTK::View* pView) override;

            private:
                // Renderer* _pRenderer;
        };

    }  // namespace Rendering

}  // namespace vEngine

#endif /* _VENGINE_RENDERING_METAL_MTK_VIEW_DELEGATE_HPP */
