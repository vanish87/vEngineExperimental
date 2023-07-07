#include <vengine/rendering/render_engine.hpp>

namespace vEngine
{
    namespace Rendering
    {
        GPUSubResource RenderEngine::GetGPUSubResource(const TextureDescriptor& desc)
        {
            GPUSubResource resource;
            resource.offset = 0;
            resource.stride = sizeof(uint8_t);
            resource.pitch = resource.stride * GetByteSize(desc.format) * desc.width;

            resource.data = (void*)desc.raw_data.data();
            resource.count = desc.raw_data.size();

            return resource;
        }
        GPUSubResource RenderEngine::GetGPUSubResource(const vEngineCameraConstantBuffer& desc) {

            GPUSubResource resource;
            resource.offset = 0;
            resource.stride = sizeof(vEngineCameraConstantBuffer);
            resource.count = 1;
            resource.pitch = 0;
            resource.total_byte_size = resource.count * resource.stride;
            return resource;
        }
    }  // namespace Rendering
}  // namespace vEngine