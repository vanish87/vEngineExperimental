
#include <vengine/rendering/metal_render_object_factory.hpp>

#include <METAL_RENDERING_PLUGIN_API.hpp>
// #include <vengine/rendering/metal_frame_buffer.hpp>
// #include <vengine/rendering/metal_graphics_buffer.hpp>
// #include <vengine/rendering/metal_pipeline_state.hpp>
// #include <vengine/rendering/metal_texture.hpp>

namespace vEngine
{
    namespace Rendering
    {
        MetalRenderObjectFactory::MetalRenderObjectFactory() : Core::GameObjectFactory() {}
        MetalRenderObjectFactory::~MetalRenderObjectFactory()
        {
            // this->d3d_swap_chain_.Reset();
            // this->d3d_imm_context_.Reset();
            // this->d3d_device_.Reset();
        }
        Core::GameObjectSharedPtr MetalRenderObjectFactory::Create(std::any parameter)
        {
            // virtual PipelineStateSharedPtr Create(const PipelineStateDescriptor& pipeline_desc) = 0;
            // virtual TextureSharedPtr Create(const TextureDescriptor& desc) = 0;
            // virtual FrameBufferSharedPtr Create(const FrameBufferDescriptor& desc) = 0;
            // virtual GraphicsBufferSharedPtr Create(const GraphicsBufferDescriptor& desc) = 0;
            // if (auto desc = std::any_cast<TextureDescriptor>(&parameter)) return std::make_shared<MetalTexture>(*desc);
            // if (auto desc = std::any_cast<PipelineStateDescriptor>(&parameter)) return std::make_shared<MetalPipelineState>(*desc);
            // if (auto desc = std::any_cast<FrameBufferDescriptor>(&parameter)) return std::make_shared<MetalFrameBuffer>(*desc);
            // if (auto desc = std::any_cast<GraphicsBufferDescriptor>(&parameter)) return std::make_shared<MetalGraphicsBuffer>(*desc);

            PRINT(parameter.type().name())
            NOT_IMPL_ASSERT;
            return nullptr;
        }
    }  // namespace Rendering
}  // namespace vEngine

// extern "C"
// {
    METAL_RENDERING_PLUGIN_API void CreateGameObjectFactory(std::unique_ptr<vEngine::Core::GameObjectFactory>& ptr)
    {
        ptr = std::make_unique<vEngine::Rendering::MetalRenderObjectFactory>();
    }
    METAL_RENDERING_PLUGIN_API void DestoryGameObjectFactory(std::unique_ptr<vEngine::Core::GameObjectFactory>& ptr)
    {
        ptr.reset();
    }
// }