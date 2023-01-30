#include <vengine/core/resource_loader.hpp>

#include <vengine/core/iresource.hpp>

namespace vEngine
{
    namespace Core
    {

        ResourceLoader::ResourceLoader()
        {
            this->loading_thread_.Create();
        }
        ResourceLoader::~ResourceLoader()
        {
            this->loading_thread_.Quit();
            this->loading_thread_.Join();
        }

        void ResourceLoader::LoadAsync(const ResourceDescriptor& desc)
        {
            this->loading_thread_.AddToQueue(std::make_shared<ResourceLoadingJob>(desc));
        }
        void ResourceLoader::Load(const ResourceDescriptor& desc)
        {
            desc.on_load_call_back();
        }

        void ResourceLoader::AddSearchPath(const std::filesystem::path path)
        {
            auto p = path;
            if (p.is_relative()) p = std::filesystem::absolute(p);

            if (std::filesystem::exists(p) == false)
            {
                PRINT(p.string() << " Not Found");
                return;
            }

            this->search_paths_[p.string()] = p;
        }
        void ResourceLoader::AddSearchFolder(const std::string folder)
        {
            this->AddSearchPath(this->GetFilePath(folder));
        }
        std::filesystem::path ResourceLoader::GetFilePath(const std::string file_name)
        {
            for (const auto& p : this->search_paths_)
            {
                const auto path = p.second / file_name;
                if (std::filesystem::exists(path)) return path;
            }

            CHECK_AND_ASSERT(false, "Cannot find file/folder " << file_name);
            return nullptr;
        }
        void ResourceLoader::DumpCurrentPath()
        {
            PRINT("Current Searching Path: ");
            for (auto& p : this->search_paths_)
            {
                PRINT(p.second.string());
            }
        }

    }  // namespace Core

}  // namespace vEngine
