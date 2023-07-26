/// \file resource_loading_thread.hpp
/// \brief Head file for Resource Loading Thread
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx
#ifndef _VENGINE_CORE_RESOURCE_LOADING_THREAD_HPP
#define _VENGINE_CORE_RESOURCE_LOADING_THREAD_HPP

#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>
// #include <functional>

#include <engine.hpp>
#include <vengine/core/iresource.hpp>
#include <vengine/core/thread.hpp>

namespace vEngine
{
    namespace Core
    {
        class ResourceLoadingJob : public ThreadJob
        {
            public:
                ResourceLoadingJob(const ResourceDescriptor& desc);
                ~ResourceLoadingJob();

            public:
                virtual void Run() override;

            private:
                ResourceLoadingJob(){};
                ResourceDescriptor desc_;
        };
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
    }
}

#endif /* _VENGINE_CORE_RESOURCE_LOADING_THREAD_HPP */
