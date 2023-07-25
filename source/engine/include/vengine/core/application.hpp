/// \file application.hpp
/// \brief Head file for Application
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_APPLICATION_HPP
#define _VENGINE_CORE_APPLICATION_HPP

#pragma once

#include <engine.hpp>
#include <vengine/core/thread.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        /// \brief A brief class description.
        //
        /// A detailed class description, it
        /// should be 2 lines at least.
        class VENGINE_API Application : public std::enable_shared_from_this<Application>, public Thread
        {
            public:
                Application();
                virtual ~Application();

            public:
                virtual void Run();
                virtual void RunAsync();

                virtual int Main(void* para) override;
                virtual void Quit();

            protected:
                void Init();
                void Update();
                void Deinit();

                virtual void OnInit();
                virtual void OnUpdate();
                virtual void OnDeinit();

                bool should_quit_;
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_APPLICATION_HPP */
