/// \file thread.hpp
/// \brief Head file for Thread
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_THREAD_H
#define _VENGINE_CORE_THREAD_H

#pragma once

#include <string>
#include <thread>

namespace vEngine
{
    namespace Core
    {

        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class Thread
        {
            public:
                /// \brief brief constructor description.
                Thread();
                virtual ~Thread();

                virtual int Main(void* para) = 0;

                int Create(void* parameter = nullptr, std::string name = __FILE__);

                int Join();

                void Sleep(uint32_t time_in_microseconds);

            protected:
                std::string name_;
                void* parameter_;

                std::thread thread_instance_;
                // pthread_attr_t ThreadAttr;

                static void* ThreadMain(void* data);
        };

        class ThreadJob
        {
            public:
                ThreadJob(){};
                virtual ~ThreadJob(){};

                virtual void Run() = 0;
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_THREAD_H */
