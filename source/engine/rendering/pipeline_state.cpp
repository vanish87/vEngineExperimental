/// \file pipeline_state.cpp
/// \brief source file for Pipeline State
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

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
        }
        PipelineState::~PipelineState() {}
    }  // namespace Rendering
}  // namespace vEngine
