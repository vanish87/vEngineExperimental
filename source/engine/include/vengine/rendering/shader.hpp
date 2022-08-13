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
#include <vengine/core/iresource.hpp>
#include <vengine/core/game_object.hpp>
#include <vengine/core/resource_loader.hpp>
#include <vengine/core/game_object_factory.hpp>

namespace vEngine
{
    namespace Rendering
    {
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class VENGINE_API Shader : public Core::GameObject, public Core::IResource
        {
            public:

                constexpr static auto properties()
                {
                    return std::tuple_cat(
                        Core::GameObject::properties(),
                        std::make_tuple(
                            Core::property("path", &Shader::path), 
                            Core::property("type", &Shader::type), 
                            Core::property("content", &Shader::content)
                        )
                    );
                };

                static ShaderSharedPtr Default(ShaderType type)
                {
                    switch (type)
                    {
                    case ShaderType::VS:
                    {
                        static auto vs = Core::GameObjectFactory::Create<Shader>();
                        auto desc = std::make_shared<Core::ResourceDescriptor>();
                        desc->file_path = Core::ResourceLoader::GetInstance().GetFilePath("vs.hlsl");
                        vs->Load(desc);
                        vs->type = type;
                        return vs;
                    }
                    case ShaderType::PS:
                    {
                        static auto ps = Core::GameObjectFactory::Create<Shader>();
                        auto desc = std::make_shared<Core::ResourceDescriptor>();
                        desc->file_path = Core::ResourceLoader::GetInstance().GetFilePath("ps.hlsl");
                        ps->Load(desc);
                        ps->type = type;
                        return ps;
                    }
                    default:
                        break;
                    }

                    NOT_IMPL_ASSERT;

                    return nullptr;
                }

            public:
                /// \brief brief constructor description.
                Shader();
                virtual ~Shader() {}

                bool Load(const Core::ResourceDescriptorSharedPtr descriptor) override;
                Core::ResourceState CurrentState() override;

                Core::ResourceState current_state_ = Core::ResourceState::Unknown;

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
