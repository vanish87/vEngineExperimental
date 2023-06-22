/// \file material.cpp
/// \brief source file for Material
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/context.hpp>
// #include <vengine/core/resource_manager.hpp>
#include <vengine/core/game_object_factory.hpp>
#include <vengine/rendering/material.hpp>
#include <vengine/rendering/render_engine.hpp>
#include <vengine/rendering/pipeline_state.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Rendering
    {
        using namespace Core;
        /// constructor detailed defintion,
        /// should be 2 lines
        Material::Material()
        {
            PipelineStateDescriptor desc;
            this->pipeline_state_ = GameObjectFactory::Create<GameObjectType::PipelineState, PipelineState>(desc);
        }
        Material::~Material() {}

        MaterialSharedPtr Material::Default()
        {
            return GameObjectFactory::Create<GameObjectType::Material, Material>();
        }
        void Material::BindShader(const ShaderType type, const ShaderSharedPtr shader)
        {
            CHECK_ASSERT_NOT_NULL(this->pipeline_state_);
            this->pipeline_state_->shaders_[type] = shader;
        }
        void Material::BindTexture(const std::string name, const TextureSharedPtr texture)
        {
            CHECK_ASSERT(this->textures_.find(name) == this->textures_.end());
            this->textures_[name] = texture;
        }

        void Material::UpdateGPUResource()
        {
            Context::GetInstance().GetRenderEngine()->Bind(this->pipeline_state_);
            for (const auto& tex : this->textures_)
            {
                Context::GetInstance().GetRenderEngine()->Bind(tex.second);
            }
        }

    }  // namespace Rendering

}  // namespace vEngine