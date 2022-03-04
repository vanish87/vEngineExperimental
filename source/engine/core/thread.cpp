/// \file thread.cpp
/// \brief source file for Thread
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/thread.hpp>
#include <engine.hpp>

namespace vEngine
{
    namespace Core
    {
        /// constructor detailed defintion,
        /// should be 2 lines
        Thread::Thread(){

        };

        Thread::~Thread(){

        };

        int Thread::Create(void* paramter, std::string name)
        {
            this->name_ = name;
            this->parameter_ = paramter;

            // pthread_attr_init(&this->ThreadAttr);
            // pthread_attr_setdetachstate(&this->ThreadAttr, PTHREAD_CREATE_JOINABLE);

            // pthread create here
            // int rc = pthread_create(&this->ThreadNum, &this->ThreadAttr, ThreadMain, this);
            this->thread_instance_ = std::thread(ThreadMain, this);

            // pthread_attr_destroy(&this->ThreadAttr);
            // if (rc)
            {
                //    return Failure("pthread_create Error:" + std::to_string(rc));
            }

            return 0;
        };

        int Thread::Join()
        {
            this->thread_instance_.join();
            return 0;
        }

        void Thread::Sleep(uint32_t TimeInMicroSeconds)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(TimeInMicroSeconds));
        }

        void* Thread::ThreadMain(void* data)
        {
            // call virtual main here
            Thread* instance = static_cast<Thread*>(data);
            int ret = instance->Main(instance->parameter_);
            if (ret != 0)
            {
                PRINT("Thread: " << instance->thread_instance_.get_id() << "returned Error\n");
            }
            // RunningInstance->ThreadInstance.detach();
            // return value is ignored by std::thread
            return data;
        };
    }  // namespace Core

}  // namespace vEngine