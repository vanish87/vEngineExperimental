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

#include <VENGINE_API.h>
#include <engine.hpp>
#include <vengine/core/data_format.hpp>

namespace vEngine
{
    namespace Rendering
    {
		enum class TextureDimension
		{
			TD_1D,
			TD_2D,
			TD_3D,
			TD_Cure,

		};
		enum class TextureUsage
		{
			GBU_CPU = 1 << 0,
			GBU_GPU = 1 << 1,
		};
		class TextureDescriptor
		{
			TextureDimension dimension;
			DataFormat format;
			TextureUsage usage;
			// std::vector<std::pair<

		};
        /// \brief Unity-like Graphics buffer
        ///
        /// Graphics buffer could be index/vertex buffer or
		/// constant buffer.
		/// It could be used in cpu and/or gpu
		// template<typename T>
        class VENGINE_API Texture
        {
            public:
                /// \brief brief constructor description.
                Texture();

                /// class variable description
                // int public_variable_;

				TextureDescriptor descriptor_;

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
