/// \file pipeline_state.hpp
/// \brief Head file for Pipline State
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_RENDERING_PIPELINE_STATE_HPP
#define _VENGINE_RENDERING_PIPELINE_STATE_HPP

#pragma once

#include <VENGINE_API.hpp>
#include <engine.hpp>
#include <vengine/rendering/data_struct.hpp>
#include <vengine/data/meta.hpp>

namespace vEngine
{
    namespace Rendering
    {
        /// \brief Unity-like Graphics buffer
        ///
        /// Graphics buffer could be index/vertex buffer or
        /// constant buffer.
        /// It could be used in cpu and/or gpu
        // template<typename T>
        class VENGINE_API PipelineState
        {
            public:
                constexpr static auto properties()
                {
                    return std::tuple_cat(
                        // GameObject::properties(),
                        std::make_tuple(
                            Core::property("descriptor", &PipelineState::descriptor_)
                        )
                    );
                };
            public:
                /// \brief brief constructor description.
                PipelineState(const PipelineStateDescriptor& desc);
                virtual ~PipelineState();
                bool Load(ShaderType type, std::filesystem::path path);

                /// class variable description
                // int public_variable_;

                PipelineStateDescriptor descriptor_;
                std::unordered_map<ShaderType, ShaderSharedPtr> shaders_;

            public:
                /// \brief A brief function description.
                ///
                /// \param p1 Description for p1.
                /// \param p2 Description for p2.
                /// \return Description for return value.
        };
    }  // namespace Rendering
}  // namespace vEngine

#endif /* _VENGINE_RENDERING_PIPELINE_STATE_HPP */
