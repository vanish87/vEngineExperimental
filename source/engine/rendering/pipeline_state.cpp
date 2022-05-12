/// \file pipeline_state.cpp
/// \brief source file for Pipeline State
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <fstream>
#include <engine.hpp>
#include <vengine/rendering/pipeline_state.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Rendering
    {

        /// constructor detailed defintion,
        /// should be 2 lines
        PipelineState::PipelineState(const PipelineStateDescriptor& desc)
        {
            PRINT("PipelineState Base");
            this->descriptor_ = desc;

            this->vs_shader_ = std::make_shared<Shader>(this->descriptor_.vs_name);
            this->ps_shader_ = std::make_shared<Shader>(this->descriptor_.ps_name);
            
            this->Load(this->vs_shader_);
            this->Load(this->ps_shader_);
        }
        PipelineState::~PipelineState() 
        {
            // PRINT("Destory Pipeline state");
        }
        bool PipelineState::Load(ShaderSharedPtr shader)
        {
            // std::ifstream fin(shader.name + ".hlsl", std::ios::binary);
            // std::ifstream fin(shader.name + ".hlsl");
            std::ifstream fin(shader->name);

            if (!fin)
            {
                PRINT_AND_BREAK("Cannot open hlsl File ");
                return false;
            }

            fin.seekg(0, std::ios_base::end);
            auto size = fin.tellg();
            fin.seekg(0, std::ios_base::beg);
            std::vector<char> shader_content(size);

            fin.read(shader_content.data(), size);
            fin.close();

            shader->content = shader_content;

            return true;
        }
    }  // namespace Rendering
}  // namespace vEngine
