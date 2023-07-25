
#include <vengine/rendering/metal_render_engine.hpp>

#include <METAL_RENDERING_PLUGIN_API.hpp>
#include <vengine/rendering/metal_render_object_factory.hpp>
#include <vengine/core/context.hpp>
#include <vengine/core/window.hpp>

namespace vEngine
{
    namespace Rendering
    {
        using namespace Core;

        void MetalRenderEngine::Init()
        {
            this->InitPipeline();
        }
        void MetalRenderEngine::Update()
        {
            this->TriangleDraw();
        }
        void MetalRenderEngine::Deinit()
        {
            this->DeinitPipeline();
        }
        void MetalRenderEngine::PrintInfo()
        {
            // auto device = MTL::CreateSystemDefaultDevice();
        }
        const char* shaderSrc = R"(
        #include <metal_stdlib>
        using namespace metal;

        struct v2f
        {
            float4 position [[position]];
            half3 color;
        };

        v2f vertex vertexMain( uint vertexId [[vertex_id]],
                               device const float3* positions [[buffer(0)]],
                               device const float3* colors [[buffer(1)]] )
        {
            v2f o;
            o.position = float4( positions[ vertexId ], 1.0 );
            o.color = half3 ( colors[ vertexId ] );
            return o;
        }

        half4 fragment fragmentMain( v2f in [[stage_in]] )
        {
            return half4( in.color, 1.0 );
        }
    )";
        void MetalRenderEngine::InitPipeline()
        {

            // _pViewController = UI::ViewController::alloc()->init( nil, nil );

            auto window = Context::GetInstance().CurrentWindow();
            auto device = MTL::CreateSystemDefaultDevice();
            // auto _pMtkView = MTK::View::alloc()->init(frame, _pDevice);

            // this->view_ = static_cast<MTK::View*>(window->WindowHandle());

            std::cout << "Metal " << device->name()->cString(NS::UTF8StringEncoding) << std::endl;
            return;

            this->view_->setColorPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB);
            this->view_->setClearColor(MTL::ClearColor::Make(1.0, 0.0, 0.0, 1.0));

            auto res_path = NS::Bundle::mainBundle()->resourcePath();
            std::cout << "Resource Path: " << res_path->cString(NS::UTF8StringEncoding) << std::endl;

            NS::Error* pError = nullptr;
            MTL::Library* pLibrary = device->newLibrary(NS::String::string(shaderSrc, NS::UTF8StringEncoding), nullptr, &pError);
            if (!pLibrary)
            {
                std::cout << pError->localizedDescription()->utf8String() << std::endl;
                assert(false);
            }

            MTL::Function* pVertexFn = pLibrary->newFunction(NS::String::string("vertexMain", NS::UTF8StringEncoding));
            MTL::Function* pFragFn = pLibrary->newFunction(NS::String::string("fragmentMain", NS::UTF8StringEncoding));

            MTL::RenderPipelineDescriptor* pDesc = MTL::RenderPipelineDescriptor::alloc()->init();
            pDesc->setVertexFunction(pVertexFn);
            pDesc->setFragmentFunction(pFragFn);
            pDesc->colorAttachments()->object(0)->setPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB);

            this->current_pipeline_state_ = device->newRenderPipelineState(pDesc, &pError);
            if (!this->current_pipeline_state_)
            {
                std::cout << pError->localizedDescription()->utf8String() << std::endl;
                assert(false);
            }

            pVertexFn->release();
            pFragFn->release();
            pDesc->release();
            pLibrary->release();

            const size_t NumVertices = 3;

            float3 positions[NumVertices] = {{-0.8f, 0.8f, 0.0f}, {0.0f, -0.8f, 0.0f}, {+0.8f, 0.8f, 0.0f}};

            float3 colors[NumVertices] = {{1.0, 0.3f, 0.2f}, {0.8f, 1.0, 0.0f}, {0.8f, 0.0f, 1.0}};

            const size_t positionsDataSize = NumVertices * sizeof(float3);
            const size_t colorDataSize = NumVertices * sizeof(float3);

            MTL::Buffer* pVertexPositionsBuffer = device->newBuffer(positionsDataSize, MTL::ResourceStorageModeManaged);
            MTL::Buffer* pVertexColorsBuffer = device->newBuffer(colorDataSize, MTL::ResourceStorageModeManaged);

            this->vertex_buffer_ = pVertexPositionsBuffer;
            this->color_buffer_ = pVertexColorsBuffer;

            memcpy(vertex_buffer_->contents(), positions, positionsDataSize);
            memcpy(color_buffer_->contents(), colors, colorDataSize);

            vertex_buffer_->didModifyRange(NS::Range::Make(0, vertex_buffer_->length()));
            color_buffer_->didModifyRange(NS::Range::Make(0, color_buffer_->length()));

            this->command_queue_ = device->newCommandQueue();
        }
        void MetalRenderEngine::DeinitPipeline()
        {
            this->vertex_buffer_->release();
            this->color_buffer_->release();
            this->current_pipeline_state_->release();
            // this->device_->release();
        }
        void MetalRenderEngine::TriangleDraw()
        {
            NS::AutoreleasePool* pPool = NS::AutoreleasePool::alloc()->init();

            MTL::CommandBuffer* pCmd = this->command_queue_->commandBuffer();
            MTL::RenderPassDescriptor* pRpd = this->view_->currentRenderPassDescriptor();
            MTL::RenderCommandEncoder* pEnc = pCmd->renderCommandEncoder(pRpd);

            pEnc->setRenderPipelineState(this->current_pipeline_state_);
            pEnc->setVertexBuffer(this->vertex_buffer_, 0, 0);
            pEnc->setVertexBuffer(this->color_buffer_, 0, 1);
            pEnc->drawPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, NS::UInteger(0), NS::UInteger(3));

            pEnc->endEncoding();
            pCmd->presentDrawable(this->view_->currentDrawable());
            pCmd->commit();

            pPool->release();
        }

    }  // namespace Rendering
}  // namespace vEngine

extern "C"
{
    METAL_RENDERING_PLUGIN_API void CreateRenderEngine(std::unique_ptr<vEngine::Rendering::RenderEngine>& ptr)
    {
        ptr = std::make_unique<vEngine::Rendering::MetalRenderEngine>();
    }
    METAL_RENDERING_PLUGIN_API void DestoryRenderEngine(std::unique_ptr<vEngine::Rendering::RenderEngine>& ptr)
    {
        ptr.reset();
    }
}
