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

#include <VENGINE_API.hpp>
#include <engine.hpp>
#include <vengine/core/thread.hpp>

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
                ResourceLoadingJob(IResourceSharedPtr JobObj, std::function<void(IResourceSharedPtr user_data)> const& complete_callback);
                ~ResourceLoadingJob();

            public:
                virtual void Run() override;

            private:
                ResourceLoadingJob(){};
                IResourceSharedPtr resource_to_load_;
                std::function<void(IResourceSharedPtr user_data)> complete_call_back_;
        };
        class ResourceLoader
        {
                SINGLETON_CLASS(ResourceLoader)

            public:

                void LoadAsync(IResourceSharedPtr resource, std::function<void(IResourceSharedPtr user_data)> const& complete_callback = nullptr);
                // void AddSync();
            private:
                ResourceLoadingThread loading_thread_;
        };

    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_RESOURCE_LOADER_HPP */