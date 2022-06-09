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

        void ResourceLoader::LoadAsync(IResourceSharedPtr resource, std::function<void(IResourceSharedPtr user_data)> const& complete_callback /*= nullptr*/)
        {
            this->loading_thread_.AddToQueue(std::make_shared<ResourceLoadingJob>(resource, complete_callback));
        }

        void ResourceLoader::AddSearchPath(const std::string path) 
        {
            std::filesystem::path p = path;
            if(p.is_relative()) p = std::filesystem::absolute(p);

            if(std::filesystem::exists(p) == false) return;

            this->search_paths_[p.string()] = p;
        }
        std::string ResourceLoader::GetFilePath(const std::string file_name)
        {
            for(auto p = this->search_paths_.begin(); p != this->search_paths_.end(); ++p)
            {
                const auto path = p->second / file_name;
                if(std::filesystem::exists(path)) return path.string();
            }

            CHECK_ASSERT(false);
            return nullptr;
        }

        ResourceLoadingJob::ResourceLoadingJob(IResourceSharedPtr resource, std::function<void(IResourceSharedPtr user_data)> const& complete_callback /*= nullptr*/)
        {
            this->resource_to_load_ = resource;
            this->complete_call_back_ = complete_callback;
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
