/// \file texture.hpp
/// \brief Head file for Texture
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_RENDERING_TEXTURE_HPP
#define _VENGINE_RENDERING_TEXTURE_HPP

#pragma once

#include <VENGINE_API.hpp>
#include <engine.hpp>
#include <vengine/rendering/data_struct.hpp>
#include <vengine/rendering/data_format.hpp>
#include <vengine/core/game_object.hpp>
#include <vengine/core/iresource.hpp>
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
        class VENGINE_API Texture: public Core::GameObject, public Core::IResource
        {
            public:

                constexpr static auto properties()
                {
                    return std::tuple_cat(
                        Core::GameObject::properties(),
                        std::make_tuple(
                            Core::property("descriptor", &Texture::descriptor_),
                            Core::property("raw_data", &Texture::raw_data_)
                        )
                    );
                };
                /// \brief brief constructor description.
                Texture(const TextureDescriptor& desc);
                virtual ~Texture();

                void SetRawData(const std::vector<byte> data)
                {
                    this->raw_data_ = data;
                }

                bool Load(const Core::ResourceDescriptorSharedPtr descriptor) override;
                Core::ResourceState CurrentState() override;

                Core::ResourceState current_state_ = Core::ResourceState::Unknown;

                virtual void PrepareData();

                /// class variable description
                // int public_variable_;

				TextureDescriptor descriptor_;
                std::vector<byte> raw_data_;

            public:
                /// \brief A brief function description.
                ///
                /// \param p1 Description for p1.
                /// \param p2 Description for p2.
                /// \return Description for return value.
                // static Texture Create(const TextureDescriptor& desc);
        };
    }  // namespace Rendering

}  // namespace vEngine

#endif /* _VENGINE_RENDERING_TEXTURE_HPP */
