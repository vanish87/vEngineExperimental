
#include <vengine/rendering/metal_mtk_view_delegate.hpp>

namespace vEngine
{
    namespace Rendering
    {
        MetalMTKViewDelegate::MetalMTKViewDelegate(MTL::Device* pDevice) : MTL::ViewDelegate() {}
        MetalMTKViewDelegate::~MetalMTKViewDelegate() {}
        void MetalMTKViewDelegate::drawInMTKView(MTK::View* pView) {}

    }  // namespace Rendering

}  // namespace vEngine
