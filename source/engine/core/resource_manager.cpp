/// \file resource_manager.cpp
/// \brief source file for Resource Manager
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/resource_manager.hpp>
#include <vengine/core/game_object_factory.hpp>
#include <vengine/core/game_node.hpp>

#include <vengine/animation/bone_component.hpp>

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
            return std::filesystem::path(file_name);
        }

        void ResourceManager::SaveJson(const json& j, const std::filesystem::path path)
        {
            auto folder = path.parent_path();
            if(!std::filesystem::exists(folder)) std::filesystem::create_directories(folder);

            std::ofstream outfile(path.string());
            outfile << std::setw(2) << j << std::endl;
            outfile.flush();
            outfile.close();
        }
        // Save to a None-Context folder
        void ResourceManager::Save(const GameObjectSharedPtr go, const std::filesystem::path path)
        {
            this->UpdateReferencePath(go);
            auto j = ToJson(go);
            this->SaveJson(j, path);
        }
        GameObjectSharedPtr ResourceManager::Load(const std::filesystem::path path)
        {
            if (!std::filesystem::exists(path)) return nullptr;

            auto j = LoadJson(path);
            GameObjectDescriptor desc;
            FromJson(j["meta"], desc);

            return CreateAndLoadByDesc<GameObject>(desc);
        }

        std::filesystem::path ResourceManager::GetGameObjectPath(const GameObjectDescriptor& desc)
        {
            auto name = desc.name;
            auto type = ToString(desc.type);

            auto config = Context::GetInstance().CurrentConfigure();
            auto root = config.resource_bin;
            auto file_name = std::to_string(desc.uuid.AsUint()) + "_" + name + "_" + type + ".json";

            std::string illegal = ":\"\'<>%$*&+ ";
            for (auto c : illegal)
            {
                std::replace(file_name.begin(), file_name.end(), c, '_');
            }

            return root / desc.reference_path / file_name;

        }
        void ResourceManager::UpdateReferencePath(const GameObjectSharedPtr go)
        {
            std::string illegal = ":\"\'<>%$*&+ ";
            if(go->descriptor_.name == "GameObject")
            {
                go->descriptor_.name = ToString(go->descriptor_.type);
                for (auto c : illegal) std::replace(go->descriptor_.name.begin(), go->descriptor_.name.end(), c, '_');
            }

            auto config = Context::GetInstance().CurrentConfigure();
            auto context_name = config.context_name;

            std::filesystem::path path;
            auto gn = std::dynamic_pointer_cast<GameNode>(go);
            while (gn != nullptr && gn->Parent().lock() != nullptr)
            {
                path = gn->descriptor_.name / path;
                gn = gn->Parent().lock();
            }

            auto path_string = path.string();
            for (auto c : illegal)
            {
                std::replace(path_string.begin(), path_string.end(), c, '_');
            }
            go->descriptor_.reference_path = std::filesystem::path(context_name) / path_string;
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
