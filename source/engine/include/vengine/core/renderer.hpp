
/// \file renderer.hpp
/// \brief Head file for Renderer
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_RENDERER_HPP
#define _VENGINE_CORE_RENDERER_HPP

#pragma once

#include <VENGINE_API.h>
#include <vengine/core/game_object.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
		template<typename T>
        class VENGINE_API Renderer : public GameObject
        {
            public:
                /// \brief brief constructor description.
                Renderer(){};

                virtual void Render() {}

				std::shared_ptr<T> renderable_;
				MaterialSharedPtr material_;

        };
    }  // namespace Core
}  // namespace vEngine


#endif /* _VENGINE_CORE_RENDERER_HPP */
