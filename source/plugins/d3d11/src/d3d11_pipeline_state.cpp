/// \file d3d11_pipeline_state.cpp
/// \brief source file for D3D11 Pipeline State
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

// #include <vengine/core/context.hpp>
#include <vengine/rendering/d3d11_pipeline_state.hpp>
// #include <vengine/rendering/d3d11_render_engine.hpp>
// #include <vengine/rendering/d3d11_texture.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Rendering
    {
        // using namespace vEngine::Core;

        /// constructor detailed defintion,
        /// should be 2 lines
        D3D11PipelineState::D3D11PipelineState(const PipelineStateDescriptor& desc) : PipelineState(desc) {}
	}
}