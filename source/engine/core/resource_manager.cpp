/// \file resource_manager.cpp
/// \brief source file for Resource Manager
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/resource_manager.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    /// constructor detailed defintion,
    /// should be 2 lines
    namespace Core
    {
        ResourceManager::ResourceManager()
        {
            this->loading_thread_.Create();
        }
        ResourceManager::~ResourceManager()
        {
            this->loading_thread_.Quit();
            this->loading_thread_.Join();
        }

        void ResourceManager::LoadAsync(const ResourceDescriptor& desc)
        {
            this->loading_thread_.AddToQueue(std::make_shared<ResourceLoadingJob>(desc));
        }
        void ResourceManager::Load(const ResourceDescriptor& desc)
        {
            desc.on_load_call_back();
        }

        void ResourceManager::SetRoot(const std::filesystem::path root)
        {
            auto p = root;
            if (p.is_relative()) p = std::filesystem::absolute(p);
            this->resource_root_ = p;
        }

        std::filesystem::path ResourceManager::GetRoot() const
        {
            return this->resource_root_;
        }
        std::filesystem::path ResourceManager::GetFilePath(const std::string file_name)
        {
            for (const auto& file : std::filesystem::recursive_directory_iterator{this->resource_root_})
            {
                if(file.is_regular_file() && file.path().filename() == file_name)
                {
                    return file.path();
                }
            }

            CHECK_AND_ASSERT(false, "Cannot find file/folder " << file_name);
            return nullptr;
        }
        void ResourceManager::DumpCurrentPath()
        {
            PRINT("Current Root Path: " << this->resource_root_.string());
        }

    }  // namespace Core

}  // namespace vEngine
