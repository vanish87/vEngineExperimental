#ifndef _VENGINE_CORE_CONFIGURE_HPP
#define _VENGINE_CORE_CONFIGURE_HPP

#pragma once

namespace vEngine
{
    namespace Core
    {
        struct GraphicsConfigure
        {
                std::string render_plugin_name;
        };
        struct Configure
        {
                std::string app_name;
                GraphicsConfigure graphics_configure;
        };

    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_CONFIGURE_HPP */
