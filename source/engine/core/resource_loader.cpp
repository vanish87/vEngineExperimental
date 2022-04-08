#include <vengine/core/resource_loader.hpp>
#include <vengine/core/iresource.hpp>

namespace vEngine
{
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

        ResourceLoader::ResourceLoader()
        {
            this->loading_thread_.Create(nullptr);
        }
        ResourceLoader::~ResourceLoader()
        {
            this->loading_thread_.Quit();
            this->loading_thread_.Join();
        }

        void ResourceLoader::AddAsync(IResourceSharedPtr resource, std::function<void(IResourceSharedPtr user_data)> const& func /*= nullptr*/)
        {
            this->loading_thread_.AddToQueue(std::make_shared<ResourceLoadingJob>(resource, func));
        }

        ResourceLoadingJob::ResourceLoadingJob(IResourceSharedPtr resource, std::function<void(IResourceSharedPtr user_data)> const& func /*= nullptr*/)
        {
            this->resource_to_load_ = resource;
            this->complete_call_back_ = func;
        }

        ResourceLoadingJob::~ResourceLoadingJob() {}

        void ResourceLoadingJob::Run()
        {
            // ProfileLogHandler ResPro("LoadProfile");
            // Profiler ModelLoad("LoadProfiler");
            // ModelLoad.SetEnable(true);
            // ModelLoad.RegisterEventHandler(&ResPro);
            // ModelLoad.Begin(Profiler::PE_FUNCTION_CALL);
            this->resource_to_load_->Load();
            // ModelLoad.End(Profiler::PE_FUNCTION_CALL, "ResourceLoadingJob::Load::" + this->object_to_load_->GetName());
            if (this->complete_call_back_ != nullptr)
            {
                this->complete_call_back_(this->resource_to_load_);
            }
        }

    }  // namespace Core

}  // namespace vEngine
