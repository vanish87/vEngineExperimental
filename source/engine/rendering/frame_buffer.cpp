/// \file frame_buffer.cpp
/// \brief source file for Frame Buffer
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

// #include <vengine/core/context.hpp>
#include <vengine/rendering/frame_buffer.hpp>
// #include <vengine/rendering/render_engine.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Rendering
    {
        FrameBuffer::FrameBuffer(const FrameBufferDescriptor& desc)
        {
            UNUSED_PARAMETER(desc);
        }

        /// constructor detailed defintion,
        /// should be 2 lines
        FrameBuffer::FrameBuffer(TextureSharedPtr backBuffer, const FrameBufferDescriptor& desc)
        {
            UNUSED_PARAMETER(desc);
            // auto& re = Context::GetInstance().GetRenderEngine();
            this->colorTextures_.push_back(backBuffer);
        }
        FrameBuffer::~FrameBuffer() {}

        /// A detailed function description, it
        /// should be 2 lines at least.
        // int MyClass::GetVariable(int p1, float p2)
        // {
        //     UNUSED_PARAMETER(p1);
        //     UNUSED_PARAMETER(p2);
        //     return 1;
        // }
    }  // namespace Rendering
}  // namespace vEngine