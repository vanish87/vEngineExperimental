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
            return root;
        }

        void ResourceManager::Save(const GameObjectSharedPtr go, const std::filesystem::path root)
        {
            this->UpdateReferencePath(go);

            auto name = go->descriptor_.name;
            auto type = "";//ToString(desc.type);

            auto file_name = std::to_string(go->descriptor_.uuid.AsUint()) + "_" + name + "_" + type + ".json";

            std::string illegal = ":\"\'<>%$*&+ ";
            for (auto c : illegal)
            {
                std::replace(file_name.begin(), file_name.end(), c, '_');
            }

            auto ref_path = go->descriptor_.reference_path;
            auto path = root / ref_path / file_name;

            auto folder = path.parent_path();
            if(!std::filesystem::exists(folder)) std::filesystem::create_directories(folder);

            auto j = ToJson(go);
            std::ofstream outfile(path.string());
            outfile << std::setw(2) << j << std::endl;
            outfile.flush();
            outfile.close();

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
