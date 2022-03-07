/// \file mesh.cpp
/// \brief source file for Mesh
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/mesh.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {

        /// constructor detailed defintion,
        /// should be 2 lines
        Mesh::Mesh()
        {
            auto desc = GraphicsBufferDescriptor();
            this->buffer_ = vEngine::Rendering::GraphicsBuffer::Create(desc);
        }
    }  // namespace Core

}  // namespace vEngine