/// \file shader.hpp
/// \brief Head file for Shader
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_RENDERING_SHADER_HPP
#define _VENGINE_RENDERING_SHADER_HPP

#pragma once
#include <vector>
#include <engine.hpp>
#include <vengine/rendering/data_struct.hpp>

namespace vEngine
{
    namespace Rendering
    {
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class VENGINE_API Shader
        {
            public:
                /// \brief brief constructor description.
                Shader();
                Shader(const std::filesystem::path path, const ShaderType type) : path{path}, type{type} {};
                virtual ~Shader() {}

            //TODO check if shader should use shared_ptr
                constexpr static auto properties()
                {
                    return std::make_tuple(
                        // GameObject::properties(),
                        Core::property("path", &Shader::path), 
                        Core::property("type", &Shader::type),
                        Core::property("content", &Shader::content)
                        );
                };
                std::filesystem::path path;
                std::vector<char> content;
                ShaderType type;
        public:
            /// \brief A brief function description.
            ///
            /// \param p1 Description for p1.
            /// \param p2 Description for p2.
            /// \return Description for return value.
            int GetVariable(int p1, float p2);
        };
    }  // namespace Rendering
}  // namespace vEngine

#endif /* _VENGINE_RENDERING_SHADER_HPP */
