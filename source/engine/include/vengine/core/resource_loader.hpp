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
#include <condition_variable>
#include <mutex>
#include <queue>
#include <functional>

// #include <unordered_map>
#include <unordered_set>

#include <VENGINE_API.hpp>
#include <engine.hpp>
#include <vengine/core/thread.hpp>
#include <vengine/core/iruntime_module.hpp>
#include <vengine/core/iresource.hpp>

namespace vEngine
{
    namespace Core
    {
        class ResourceLoadingThread : public Thread
        {
            public:
                ResourceLoadingThread();
                ~ResourceLoadingThread();

            public:
                virtual int Main(void* para) override;

                void AddToQueue(ThreadJobSharedPtr job);
                void Quit();

            private:
                std::queue<ThreadJobSharedPtr> loading_queue_;
                std::mutex mutex_;
                std::condition_variable cond_variable_;

                bool should_quit_;
        };
        class ResourceLoadingJob : public ThreadJob
        {
            public:
                ResourceLoadingJob(IResourceSharedPtr resource, const ResourceDescriptorSharedPtr desc);
                ~ResourceLoadingJob();

            public:
                virtual void Run() override;

            private:
                ResourceLoadingJob(){};
                IResourceSharedPtr resource_to_load_;
                ResourceDescriptorSharedPtr desc_;
        };
        class VENGINE_API ResourceLoader: public IRuntimeModule
        {
                SINGLETON_CLASS(ResourceLoader)

            public:
                void Init() override{};
                void Deinit() override{};
                void Update() override{};

            public:
                void LoadAsync(IResourceSharedPtr resource, const ResourceDescriptorSharedPtr desc);
                // void AddSync();

                std::filesystem::path GetFilePath(const std::string file_name);
                void AddSearchFolder(const std::string path);
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
