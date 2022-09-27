/// \file material.cpp
/// \brief source file for Material
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/context.hpp>
#include <vengine/rendering/material.hpp>
#include <vengine/rendering/render_engine.hpp>
#include <vengine/core/resource_loader.hpp>
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
        Material::Material(const GameObjectType type) : GameObject(type)
        {
            this->pipeline_state_ = Context::GetInstance().GetRenderEngine()->Create(PipelineStateDescriptor::Default());
        }
        Material::~Material() {}

        MaterialSharedPtr Material::Default()
        {
            static auto mat = GameObjectFactory::Create<Material>();
            return mat;
        }
        void Material::BindShader(const ShaderType type, const ShaderSharedPtr shader)
        {
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
            if (this->textures_.size() > 0)
            {
                auto tex = this->textures_[0];
                Context::GetInstance().GetRenderEngine()->Bind(tex);
            }
        }

    }  // namespace Rendering

}  // namespace vEngine