/// \file graphics_buffer.cpp
/// \brief source file for graphics buffer
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <engine.hpp>
#include <vengine/rendering/graphics_buffer.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Rendering
    {

        /// constructor detailed defintion,
        /// should be 2 lines
        GraphicsBuffer::GraphicsBuffer(const GraphicsBufferDescriptor& desc) 
        {
            PRINT("Graphic Buffer Base");
            this->descriptor_ = desc;

        }
        GraphicsBuffer::~GraphicsBuffer() {}

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