/// \file renderer.hpp
/// \brief Head file for Renderer
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_RENDER_COMPONENT_HPP
#define _VENGINE_CORE_RENDER_COMPONENT_HPP

#pragma once

#include <VENGINE_API.h>
#include <vengine/core/component.hpp>


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
        class VENGINE_API RendererComponent : public Component<Renderer<T>>
        {
            public:
                /// \brief brief constructor description.
                RendererComponent(){};
        };
    }  // namespace Core
}  // namespace vEngine


#endif /* _VENGINE_CORE_RENDER_COMPONENT_HPP */
