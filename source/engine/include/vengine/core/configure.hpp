/// \file configure.hpp
/// \brief Head file for Configure
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_CONFIGURE_HPP
#define _VENGINE_CORE_CONFIGURE_HPP

#pragma once

#include <filesystem>
#include <vector>

namespace vEngine
{
    namespace Core
    {
        enum class Output
        {
            Window,
            CommandLine,
            Offline,
        };
        struct GraphicsConfigure
        {
                std::string render_plugin_name = "empty_plugin";
                Output output = Output::Window;
                int width = 640;
                int height = 480;
                void* wnd = nullptr;
        };
        struct Configure
        {
                std::string app_name = "vEngineApp";
                std::string context_name = "default_context";
                std::string custom_plugin_name = "custom_plugin";
                std::filesystem::path source_root = "./";
                std::filesystem::path bin_root = "./bin";
                std::filesystem::path resource_src = "./resource";
                std::filesystem::path resource_bin = "./resource";
                std::filesystem::path library_bin = "./";
                std::vector<std::string> argv;
                GraphicsConfigure graphics_configure;

                void ImportArgs(const int argc, const char* argv_in[])
                {
                    this->argv.clear();
                    for(auto i = 0; i < argc; ++i)
                    {
                        this->argv.push_back(argv_in[i]);
                    }
                }
        };

    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_CONFIGURE_HPP */
