/// \file resource_loader.hpp
/// \brief Head file for loading resource async
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_RESOURCE_MANAGER_HPP
#define _VENGINE_CORE_RESOURCE_MANAGER_HPP

#pragma once

#include <unordered_map>
#include <stack>
#include <unordered_set>
#include <filesystem>

#include <engine.hpp>
#include <vengine/core/resource_loading_thread.hpp>
#include <vengine/core/iruntime_module.hpp>
#include <vengine/core/iresource.hpp>
#include <vengine/core/game_object.hpp>

namespace vEngine
{
    namespace Core
    {
        class VENGINE_API ResourceManager: public IRuntimeModule
        {
                SINGLETON_CLASS(ResourceManager)

            public:
                void Init() override;
                void Deinit() override;
                void Update() override{};

            public:
                std::filesystem::path GetFilePath(const std::string file_name);
                void LoadAsync(const ResourceDescriptor& desc);
                void Load(const ResourceDescriptor& desc);

                void Save(const GameObjectSharedPtr go, const std::filesystem::path path);
                std::filesystem::path GetGameObjectPath(const GameObjectDescriptor& desc);
                GameObjectSharedPtr Load(const std::filesystem::path path);
                // void AddSync();

                // std::filesystem::path GetFilePath(const std::string file_name);
                // std::filesystem::path GetFilePath(const GameObjectDescriptor& desc);
                void UpdateReferencePath(const GameObjectSharedPtr go);
                // void SetRoot(const std::filesystem::path root);
                // std::filesystem::path GetRoot() const;
                // void AddSearchFolder(const std::string folder);
                // void AddSearchPath(const std::filesystem::path path);

                // void DumpCurrentPath();

                void Register(const GameObjectSharedPtr go, bool isDynamic = false);
                void Unregister(const GameObjectSharedPtr go);
                void AddPendingSave(const GameObjectSharedPtr go);
                void Save(const GameObjectSharedPtr go);
                GameObjectSharedPtr Load(const GameObjectDescriptor&  desc);
                void FlushPending();
                GameObjectSharedPtr FindOrLoad(const GameObjectDescriptor& desc);

            private:
                ResourceLoadingThread loading_thread_;

                // std::filesystem::path resource_root_;
                // std::unordered_map<std::string, std::filesystem::path> search_paths_;
                // std::unordered_set<std::filesystem::path> search_paths_;

                std::unordered_map<UUID, GameObjectSharedPtr> runtime_objects_;
                std::stack<GameObjectSharedPtr> pending_objects_;
                std::unordered_set<UUID> pending_uuids_;
                std::unordered_map<UUID, GameObjectSharedPtr> runtime_dynamic_objects_;// context related objects
        };

    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_RESOURCE_MANAGER_HPP */
