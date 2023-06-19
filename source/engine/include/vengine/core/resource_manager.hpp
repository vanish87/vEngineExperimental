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
                std::filesystem::path GetSourceFilePath(const std::string file_name);
                void LoadAsync(const ResourceDescriptor& desc);
                void Load(const ResourceDescriptor& desc);

                void SaveAsReference(const GameObjectSharedPtr go, const std::filesystem::path path);
                GameObjectSharedPtr LoadAsReference(const std::filesystem::path path);

                void Register(const GameObjectSharedPtr go, bool isDynamic = false);
                void Unregister(const GameObjectSharedPtr go);


                void SaveAsValue(const GameObjectSharedPtr go);
                GameObjectSharedPtr LoadAsValue(const GameObjectDescriptor& desc);

                void AddPendingSave(const GameObjectSharedPtr go);
                void FlushPending();
                GameObjectSharedPtr FindOrCreate(const GameObjectDescriptor& desc);

            private:
                ResourceLoadingThread loading_thread_;

                // std::filesystem::path resource_root_;
                // std::unordered_map<std::string, std::filesystem::path> search_paths_;
                // std::unordered_set<std::filesystem::path> search_paths_;

                std::unordered_map<UUID, GameObjectSharedPtr> runtime_objects_;
                std::stack<GameObjectSharedPtr> pending_objects_;
                std::unordered_set<UUID> pending_uuids_;
        };

    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_RESOURCE_MANAGER_HPP */
