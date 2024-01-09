/// \file mesh_renderer.cpp
/// \brief source file for Mesh Renderer
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/rendering/mesh_renderer.hpp>
#include <vengine/core/game_object_factory.hpp>
#include <vengine/core/context.hpp>
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

        MeshRendererSharedPtr MeshRenderer::Default()
        {
            return GameObjectFactory::Create<Core::GameObjectType::MeshRenderer, MeshRenderer>();
        }
        /// constructor detailed defintion,
        /// should be 2 lines
        MeshRenderer::MeshRenderer()
        {
            VE_INFO("Mesh renderer created");
        }
        MeshRenderer::~MeshRenderer() {}
        void MeshRenderer::Render()
        {
            auto& re = Context::GetInstance().GetRenderEngine();
            auto mesh = this->renderable_;
            if (mesh != nullptr)
            {
                mesh->UpdateGPUBuffer();

                // Set gpu variable for material here
                this->material_->UpdateGPUResource();

                // VE_INFO("MeshRenderer Call re.Render(vertex, index)");
                re->Render(mesh->vertex_buffer_, mesh->index_buffer_);

                // re.PrintInfo();
            }
            else
            {
                VE_INFO("Mesh is null");
            }
        }
    }  // namespace Rendering

}  // namespace vEngine