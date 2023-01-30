/// \file resource_loader.hpp
/// \brief Head file for loading resource async
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_RESOURCE_LOADER_HPP
#define _VENGINE_CORE_RESOURCE_LOADER_HPP

#pragma once

#include <unordered_map>
// #include <unordered_set>
#include <filesystem>

#include <engine.hpp>
#include <vengine/core/resource_loading_thread.hpp>
#include <vengine/core/iruntime_module.hpp>
#include <vengine/core/iresource.hpp>

namespace vEngine
{
    namespace Core
    {
        class VENGINE_API ResourceLoader: public IRuntimeModule
        {
                SINGLETON_CLASS(ResourceLoader)

            public:
                void Init() override{};
                void Deinit() override{};
                void Update() override{};

            public:
                void LoadAsync(const ResourceDescriptor& desc);
                void Load(const ResourceDescriptor& desc);
                // void AddSync();

                std::filesystem::path GetFilePath(const std::string file_name);
                void AddSearchFolder(const std::string folder);
                void AddSearchPath(const std::filesystem::path path);

                void DumpCurrentPath();

            private:
                ResourceLoadingThread loading_thread_;

                std::unordered_map<std::string, std::filesystem::path> search_paths_;
                // std::unordered_set<std::filesystem::path> search_paths_;
        };

    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_RESOURCE_LOADER_HPP */
