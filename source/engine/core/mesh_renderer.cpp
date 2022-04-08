/// \file mesh_renderer.cpp
/// \brief source file for Mesh Renderer
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/context.hpp>
#include <vengine/core/mesh.hpp>
#include <vengine/core/mesh_renderer.hpp>
#include <vengine/core/mesh_renderer_component.hpp>
#include <vengine/rendering/render_engine.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {

        /// constructor detailed defintion,
        /// should be 2 lines
        MeshRenderer::MeshRenderer()
        {
            PRINT("Mesh renderer created");
        }
        void MeshRenderer::Render()
        {
            auto& re = Context::GetInstance().GetRenderEngine();
            auto mesh = this->renderable_;
            if (mesh != nullptr)
            {
                mesh->UpdateGPUBuffer();

                PRINT("MeshRenderer Call re.Render(vertex, index)");
                re.Render(mesh->vertex_buffer_, mesh->index_buffer_);

                re.PrintInfo();
            }
            else
            {
                PRINT("Mesh is null");
            }
        }
    }  // namespace Core

}  // namespace vEngine