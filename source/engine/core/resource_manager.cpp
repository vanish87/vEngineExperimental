/// \file resource_manager.cpp
/// \brief source file for Resource Manager
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/resource_manager.hpp>
#include <vengine/core/game_node.hpp>
#include <vengine/data/json.hpp>

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
        void ResourceManager::Init()
        {
            auto config = Context::GetInstance().CurrentConfigure();
            auto path = config.resource_bin / config.context_name / "uuid.json";
            if (!std::filesystem::exists(path)) return;

            auto j = LoadJson(path);
            FromJson(j, UUIDGenerator::GetInstance());
        }
        void ResourceManager::Deinit()
        {
            auto config = Context::GetInstance().CurrentConfigure();
            auto path = config.resource_bin / config.context_name / "uuid.json";
            auto j = ToJson(UUIDGenerator::GetInstance());
            SaveJson(j, path);
        }

        void ResourceManager::LoadAsync(const ResourceDescriptor& desc)
        {
            this->loading_thread_.AddToQueue(std::make_shared<ResourceLoadingJob>(desc));
        }
        void ResourceManager::Load(const ResourceDescriptor& desc)
        {
            desc.on_load_call_back();
        }

        std::filesystem::path ResourceManager::GetFilePath(const std::string file_name)
        {
            auto config = Context::GetInstance().CurrentConfigure();
            auto root = config.resource_src;
            for (const auto& file : std::filesystem::recursive_directory_iterator{root})
            {
                if(file.is_regular_file() && file.path().filename() == file_name)
                {
                    return file.path();
                }
            }

            CHECK_AND_ASSERT(false, "Cannot find file/folder " << file_name);
            return nullptr;
        }

        void ResourceManager::Save(const GameObjectSharedPtr go, const std::filesystem::path path)
        {
            this->UpdateReferencePath(go);

            auto folder = path.parent_path();
            if (!std::filesystem::exists(folder)) std::filesystem::create_directories(folder);

            auto j = ToJson(go);
            SaveJson(j, path);
        }
        GameObjectSharedPtr ResourceManager::Load(const std::filesystem::path path)
        {
            if (!std::filesystem::exists(path)) return nullptr;

            auto j = LoadJson(path);
            GameObjectDescriptor desc;
            FromJson(j["meta"], desc);

            return CreateAndLoadByDesc<GameObject>(desc);
        }

        void ResourceManager::UpdateReferencePath(const GameObjectSharedPtr go)
        {
            auto config = Context::GetInstance().CurrentConfigure();
            auto context_name = config.context_name;

            std::filesystem::path path = context_name;
            auto gn = std::dynamic_pointer_cast<GameNode>(go);
            while (gn != nullptr && gn->Parent().lock() != nullptr)
            {
                path = gn->descriptor_.name / path;
                gn = gn->Parent().lock();
            }
            go->descriptor_.reference_path = path;
        }

        // std::filesystem::path ResourceManager::GetFilePath(const std::string file_name)
        // {
        //     for (const auto& file : std::filesystem::recursive_directory_iterator{this->resource_root_})
        //     {
        //         if(file.is_regular_file() && file.path().filename() == file_name)
        //         {
        //             return file.path();
        //         }
        //     }

        //     CHECK_AND_ASSERT(false, "Cannot find file/folder " << file_name);
        //     return nullptr;
        // }
        // void ResourceManager::DumpCurrentPath()
        // {
        //     PRINT("Current Root Path: " << this->resource_root_.string());
        // }

    }  // namespace Core

}  // namespace vEngine
