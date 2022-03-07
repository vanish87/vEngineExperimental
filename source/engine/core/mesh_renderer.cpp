/// \file mesh_renderer.cpp
/// \brief source file for Mesh Renderer
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/context.hpp>
#include <vengine/core/mesh_renderer.hpp>
#include <vengine/core/mesh.hpp>
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
			PRINT("Mesh renderer");
		}
        void MeshRenderer::Render()
        {
            auto& re = Context::GetInstance().GetRenderEngine();
            auto mesh = this->renderable_;

			MeshRendererComponent meshRendererComponent;
			// auto pos = meshRendererComponent.transform_;

			auto meshRenderer = meshRendererComponent.game_object_;
			meshRenderer->Render();
			meshRenderer->uuid_;

			auto originalMesh = meshRenderer->renderable_;
			auto originalMaterial = meshRenderer->material_;
			originalMesh->uuid_;
			auto indexBuffer = originalMesh->buffer_;

			re.PrintInfo();
        }
    }  // namespace Core

}  // namespace vEngine