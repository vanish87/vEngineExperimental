#ifndef _VENGINE_CORE_CONFIGURE_HPP
#define _VENGINE_CORE_CONFIGURE_HPP

#pragma once

#include <filesystem>

namespace vEngine
{
    namespace Core
    {
        struct GraphicsConfigure
        {
                std::string render_plugin_name = "empty_plugin";
                int width = 640;
                int height = 480;
        };
        struct Configure
        {
                std::string app_name = "vEngineApp";
                std::string context_name = "default_context";
                std::filesystem::path resource_root;
                GraphicsConfigure graphics_configure;
        };

    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_CONFIGURE_HPP */
