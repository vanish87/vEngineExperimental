
#include <vengine/rendering/metal_render_engine.hpp>

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
            this->device_ = MTL::CreateSystemDefaultDevice();
            auto window = Context::GetInstance().CurrentWindow();

#ifdef VENGINE_PLATFORM_TARGET_IOS
            CGRect frame = UI::Screen::mainScreen()->bounds();
            this->ui_view_controller_ = UI::ViewController::alloc()->init(nil, nil);

            this->mtk_view_ = MTK::View::alloc()->init(frame, this->device_);
            auto ui_window = reinterpret_cast<UI::Window*>(window->WindowHandle());

            auto mtkView = reinterpret_cast<UI::View*>(this->mtk_view_);
            mtkView->setAutoresizingMask(UI::ViewAutoresizingFlexibleWidth | UI::ViewAutoresizingFlexibleHeight);
            this->ui_view_controller_->view()->addSubview(mtkView);
            ui_window->setRootViewController(this->ui_view_controller_);
            ui_window->makeKeyAndVisible();
#else
            CGRect frame = (CGRect){{100.0, 100.0}, {512.0, 512.0}};
            this->mtk_view_ = MTK::View::alloc()->init(frame, this->device_);

            auto ns_window = reinterpret_cast<NS::Window*>(window->WindowHandle());
            ns_window->setContentView(this->mtk_view_);
            ns_window->makeKeyAndOrderFront(nullptr);
#endif

            std::cout << "Metal " << this->device_->name()->cString(NS::UTF8StringEncoding) << std::endl;

            this->mtk_view_->setColorPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB);
            this->mtk_view_->setClearColor(MTL::ClearColor::Make(0.0, 0.0, 0.0, 1.0));

            this->command_queue_ = this->device_->newCommandQueue();

            using NS::StringEncoding::UTF8StringEncoding;

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

            NS::Error* pError = nullptr;
            MTL::Library* pLibrary = this->device_->newLibrary(NS::String::string(shaderSrc, UTF8StringEncoding), nullptr, &pError);
            if (!pLibrary)
            {
                __builtin_printf("%s", pError->localizedDescription()->utf8String());
                assert(false);
            }

            MTL::Function* pVertexFn = pLibrary->newFunction(NS::String::string("vertexMain", UTF8StringEncoding));
            MTL::Function* pFragFn = pLibrary->newFunction(NS::String::string("fragmentMain", UTF8StringEncoding));

            MTL::RenderPipelineDescriptor* pDesc = MTL::RenderPipelineDescriptor::alloc()->init();
            pDesc->setVertexFunction(pVertexFn);
            pDesc->setFragmentFunction(pFragFn);
            pDesc->colorAttachments()->object(0)->setPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB);

            this->current_pipeline_state_ = this->device_->newRenderPipelineState(pDesc, &pError);
            if (!this->current_pipeline_state_)
            {
                __builtin_printf("%s", pError->localizedDescription()->utf8String());
                assert(false);
            }

            pVertexFn->release();
            pFragFn->release();
            pDesc->release();
            pLibrary->release();

            const size_t NumVertices = 3;

            float4 positions[NumVertices] = {{-0.8f, 0.8f, 0.0f, 1}, {0.0f, -0.8f, 0.0f, 1}, {+0.8f, 0.8f, 0.0f, 1}};

            float4 colors[NumVertices] = {{1.0, 0.0f, 0.0f, 1}, {0.0f, 1.0, 0.0f, 1}, {0.0f, 0.0f, 1.0, 1}};

            const size_t positionsDataSize = NumVertices * sizeof(float4);
            const size_t colorDataSize = NumVertices * sizeof(float4);

            MTL::Buffer* pVertexPositionsBuffer = this->device_->newBuffer(positionsDataSize, MTL::ResourceStorageModeShared);
            MTL::Buffer* pVertexColorsBuffer = this->device_->newBuffer(colorDataSize, MTL::ResourceStorageModeShared);

            this->vertex_buffer_ = pVertexPositionsBuffer;
            this->color_buffer_ = pVertexColorsBuffer;

            memcpy(this->vertex_buffer_->contents(), positions, positionsDataSize);
            memcpy(this->color_buffer_->contents(), colors, colorDataSize);

            this->TriangleDraw();
        }
        void MetalRenderEngine::DeinitPipeline()
        {
            this->vertex_buffer_->release();
            this->color_buffer_->release();
            this->current_pipeline_state_->release();
            this->command_queue_->release();

            this->device_->release();
            this->mtk_view_->release();
            if (this->ui_view_controller_ != nullptr) this->ui_view_controller_->release();
        }
        void MetalRenderEngine::TriangleDraw()
        {
            NS::AutoreleasePool* pPool = NS::AutoreleasePool::alloc()->init();

            MTL::CommandBuffer* pCmd = this->command_queue_->commandBuffer();
            MTL::RenderPassDescriptor* pRpd = this->mtk_view_->currentRenderPassDescriptor();
            MTL::RenderCommandEncoder* pEnc = pCmd->renderCommandEncoder(pRpd);

            pEnc->setRenderPipelineState(this->current_pipeline_state_);
            pEnc->setVertexBuffer(this->vertex_buffer_, 0, 0);
            pEnc->setVertexBuffer(this->color_buffer_, 0, 1);
            pEnc->drawPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, NS::UInteger(0), NS::UInteger(3));

            pEnc->endEncoding();
            pCmd->presentDrawable(this->mtk_view_->currentDrawable());
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
