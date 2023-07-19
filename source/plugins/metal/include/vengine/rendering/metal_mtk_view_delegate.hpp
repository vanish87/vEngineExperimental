#ifndef _VENGINE_RENDERING_METAL_MTK_VIEW_DELEGATE_HPP
#define _VENGINE_RENDERING_METAL_MTK_VIEW_DELEGATE_HPP

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
