
#include <vengine/rendering/metal_render_engine.hpp>

namespace vEngine
{
    namespace Rendering
    {

        void MetalRenderEngine::Init()
        {
        }
        void MetalRenderEngine::Update() {}
        void MetalRenderEngine::Deinit() {}
        void MetalRenderEngine::PrintInfo()
        {
            auto device = MTL::CreateSystemDefaultDevice();
            std::cout << "Metal" << std::endl;
            std::cout << device->name()->cString(NS::UTF8StringEncoding) << std::endl;
        }

    }  // namespace Rendering
}  // namespace vEngine

extern "C"
{
    void CreateRenderEngine(std::unique_ptr<vEngine::Rendering::RenderEngine>& ptr)
    {
        ptr = std::make_unique<vEngine::Rendering::MetalRenderEngine>();
    }
    void DestoryRenderEngine(std::unique_ptr<vEngine::Rendering::RenderEngine>& ptr)
    {
        ptr.reset();
    }
}