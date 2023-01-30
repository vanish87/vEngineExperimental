/// \file resource_loading_thread.cpp
/// \brief source file for Resource Leading Thread
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/resource_loading_thread.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    /// constructor detailed defintion,
    /// should be 2 lines
    namespace Core
    {

        ResourceLoadingThread::ResourceLoadingThread() {}

        ResourceLoadingThread::~ResourceLoadingThread() {}

        int ResourceLoadingThread::Main(void* para)
        {
            UNUSED_PARAMETER(para);

            auto ret = 0;
            while (!this->should_quit_)
            {
                std::unique_lock<std::mutex> lk(mutex_);
                while (this->loading_queue_.empty())
                {
                    cond_variable_.wait(lk);
                    if (this->should_quit_) return ret;
                }
                auto job = loading_queue_.front();
                loading_queue_.pop();
                lk.unlock();
                job->Run();
                job.reset();
                this->Sleep(10);
            }

            return ret;
        }

        void ResourceLoadingThread::AddToQueue(ThreadJobSharedPtr job)
        {
            std::unique_lock<std::mutex> lk(mutex_);
            this->loading_queue_.push(job);
            this->cond_variable_.notify_one();
        }

        void ResourceLoadingThread::Quit()
        {
            this->should_quit_ = true;
            this->cond_variable_.notify_one();
        }

        ResourceLoadingJob::ResourceLoadingJob(const ResourceDescriptor& desc)
        {
            this->desc_ = desc;
        }

        ResourceLoadingJob::~ResourceLoadingJob() {}

        void ResourceLoadingJob::Run()
        {
            // ProfileLogHandler ResPro("LoadProfile");
            // Profiler ModelLoad("LoadProfiler");
            // ModelLoad.SetEnable(true);
            // ModelLoad.RegisterEventHandler(&ResPro);
            // ModelLoad.Begin(Profiler::PE_FUNCTION_CALL);
            if (this->desc_.on_load_call_back != nullptr)
            {
                this->desc_.on_load_call_back();
            }
            // ModelLoad.End(Profiler::PE_FUNCTION_CALL, "ResourceLoadingJob::Load::" + this->object_to_load_->GetName());
            // if (this->desc_.on_complete_call_back != nullptr)
            // {
            //     this->desc_.on_complete_call_back(ptr);
            // }
        }

    }  // namespace Core

}  // namespace vEngine
