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
#include <vengine/rendering/mesh_renderer.hpp>
#include <vengine/rendering/mesh_renderer_component.hpp>
#include <vengine/rendering/render_engine.hpp>
#include <vengine/rendering/material.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Rendering
    {
        using namespace Core;

        /// constructor detailed defintion,
        /// should be 2 lines
        MeshRenderer::MeshRenderer(const GameObjectType type) : Renderer(type)
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

                // Set gpu variable for material here
                this->material_->UpdateGPUResource();

                // PRINT("MeshRenderer Call re.Render(vertex, index)");
                re->Render(mesh->vertex_buffer_, mesh->index_buffer_);

                // re.PrintInfo();
            }
            else
            {
                PRINT("Mesh is null");
            }
        }
    }  // namespace Core

}  // namespace vEngine