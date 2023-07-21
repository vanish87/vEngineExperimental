/// \file d3d11_frame_buffer.cpp
/// \brief source file for D3D11 FrameBuffer
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

// #include <vengine/core/context.hpp>
#include <vengine/rendering/d3d11_frame_buffer.hpp>
// #include <vengine/rendering/d3d11_render_engine.hpp>
// #include <vengine/rendering/d3d11_texture.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Rendering
    {
        // using namespace vEngine::Core;

        /// constructor detailed defintion,
        /// should be 2 lines
        D3D11FrameBuffer::D3D11FrameBuffer(const FrameBufferDescriptor& desc) : FrameBuffer(desc) {}
        // D3D11FrameBuffer::D3D11FrameBuffer(TextureSharedPtr backBuffer, const FrameBufferDescriptor& desc) : FrameBuffer(backBuffer, desc) {}

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