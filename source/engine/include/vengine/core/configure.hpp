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
                int width;
                int height;

                GraphicsConfigure() : render_plugin_name{"empty_plugin"}, width{640}, height{480} {}
        };
        struct Configure
        {
                std::string app_name;
                GraphicsConfigure graphics_configure;
                Configure() : app_name{"vEngine_Example"} {}
        };

    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_CONFIGURE_HPP */
