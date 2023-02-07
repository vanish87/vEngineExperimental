
#include <vengine/rendering/d3d11_render_object_factory.hpp>

#include <vengine/rendering/d3d11_frame_buffer.hpp>
#include <vengine/rendering/d3d11_graphics_buffer.hpp>
#include <vengine/rendering/d3d11_pipeline_state.hpp>
#include <vengine/rendering/d3d11_texture.hpp>

namespace vEngine
{
    namespace Rendering
    {
        D3D11RenderObjectFactory::D3D11RenderObjectFactory() : Core::GameObjectFactory() {}
        D3D11RenderObjectFactory::~D3D11RenderObjectFactory()
        {
            // this->d3d_swap_chain_.Reset();
            // this->d3d_imm_context_.Reset();
            // this->d3d_device_.Reset();
        }
        Core::GameObjectSharedPtr D3D11RenderObjectFactory::Create(std::any parameter)
        {
            // virtual PipelineStateSharedPtr Create(const PipelineStateDescriptor& pipeline_desc) = 0;
            // virtual TextureSharedPtr Create(const TextureDescriptor& desc) = 0;
            // virtual FrameBufferSharedPtr Create(const FrameBufferDescriptor& desc) = 0;
            // virtual GraphicsBufferSharedPtr Create(const GraphicsBufferDescriptor& desc) = 0;
            if (auto desc = std::any_cast<TextureDescriptor>(&parameter)) return std::make_shared<D3D11Texture>(*desc);
            if (auto desc = std::any_cast<PipelineStateDescriptor>(&parameter)) return std::make_shared<D3D11PipelineState>(*desc);
            if (auto desc = std::any_cast<FrameBufferDescriptor>(&parameter)) return std::make_shared<D3D11FrameBuffer>(*desc);
            if (auto desc = std::any_cast<GraphicsBufferDescriptor>(&parameter)) return std::make_shared<D3D11GraphicsBuffer>(*desc);

            PRINT(parameter.type().name())
            NOT_IMPL_ASSERT;
            return nullptr;
        }
    }  // namespace Rendering
}  // namespace vEngine

extern "C"
{
    void CreateGameObjectFactory(std::unique_ptr<vEngine::Core::GameObjectFactory>& ptr)
    {
        ptr = std::make_unique<vEngine::Rendering::D3D11RenderObjectFactory>();
    }
    void DestoryGameObjectFactory(std::unique_ptr<vEngine::Core::GameObjectFactory>& ptr)
    {
        ptr.reset();
    }
}