/// \file pipeline_state.cpp
/// \brief source file for Pipeline State
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

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
        // PipelineState::PipelineState(const GameObjectType type): GameObject(type){}
        PipelineState::PipelineState(const PipelineStateDescriptor desc)
        {
            // VE_INFO("PipelineState Base");
            this->descriptor_ = desc;
        }
        PipelineState::~PipelineState()
        {
            // VE_INFO("Destory Pipeline state");
        }
        void PipelineState::PrepareData()
        {

        }
        // bool PipelineState::Load(const ShaderType type, const std::filesystem::path path)
        // {
        //     // std::ifstream fin(shader.name + ".hlsl", std::ios::binary);
        //     // std::ifstream fin(shader.name + ".hlsl");
        //     std::ifstream fin(path.string());

        //     if (!fin)
        //     {
        //         VE_ASSERT(false,"Cannot open hlsl File ");
        //         return false;
        //     }

        //     fin.seekg(0, std::ios_base::end);
        //     auto size = fin.tellg();
        //     fin.seekg(0, std::ios_base::beg);
        //     std::vector<char> shader_content(size);

        //     fin.read(shader_content.data(), size);
        //     fin.close();

        //     VE_ASSERT(this->shaders_.find(type) == this->shaders_.end());

        //     auto shader = std::make_shared<Shader>(path, type);
        //     shader->content = shader_content;
        //     this->shaders_[type] = shader;

        //     return true;
        // }
    }  // namespace Rendering
}  // namespace vEngine
