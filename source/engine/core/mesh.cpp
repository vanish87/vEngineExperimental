/// \file mesh.cpp
/// \brief source file for Mesh
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/mesh.hpp>
#include <vengine/core/context.hpp>
#include <vengine/rendering/render_engine.hpp>

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
            GraphicsBufferDescriptor desc;
            this->buffer_ = Context::GetInstance().GetRenderEngine().Create(desc);
        }
    }  // namespace Core

}  // namespace vEngine