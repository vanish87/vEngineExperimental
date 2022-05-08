/// \file mesh_renderer_component.hpp
/// \brief Head file for Mesh Renderer Component
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_MESH_RENDERER_COMPONENT_HPP
#define _VENGINE_CORE_MESH_RENDERER_COMPONENT_HPP

#include <cstring>
#include <vengine/core/component.hpp>
#include <vengine/core/mesh_renderer.hpp>
#include <vengine/core/mesh_component.hpp>
#include <vengine/rendering/graphics_buffer.hpp>

#include <vengine/core/context.hpp>
#include <vengine/rendering/render_engine.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Rendering
    {
        using namespace vEngine::Core;
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class MeshRendererComponent : public Component<MeshRenderer>
        {
            public:
                /// \brief brief constructor description.
                MeshRendererComponent();

                void OnBeginRender()
                {
                    vEngineObjectConstantBuffer cb;
                    cb.local_to_world_matrix = this->LocalToWorldTransform();
                    auto data = this->mesh_constant_buffer_->Map();
                    std::memcpy(data.data, &cb, sizeof(vEngineObjectConstantBuffer));
                    this->mesh_constant_buffer_->Unmap();

                    Context::GetInstance().GetRenderEngine().OnBind(this->mesh_constant_buffer_);

                }

                virtual void Update(GameNodeSharedPtr parent) override
                {
                    //Update local to world matrix for current game node
                    // PRINT("MeshRendererComponent Update");
                    if(this->game_object_->renderable_ == nullptr)
                    {
                        auto meshComponent = parent->FirstOf<MeshComponent>();
                        this->game_object_->renderable_ = meshComponent->game_object_;
                    }

                    this->UpdateLocal(parent);
                };

                //world matrix etc.
                GraphicsBufferSharedPtr mesh_constant_buffer_;
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_MESH_RENDERER_COMPONENT_HPP */
