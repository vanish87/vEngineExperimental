#ifndef _VENGINE_CORE_TIMER_HPP
#define _VENGINE_CORE_TIMER_HPP
#pragma once

#ifdef VENGINE_PLATFORM_WINDOWS
    #define USE_WINDOWS_TIME_QUERY
#endif

#ifdef USE_WINDOWS_TIME_QUERY
    #include <windows.h>
#else
    #include <chrono>
#endif

#include <engine.hpp>

namespace vEngine
{
    namespace Core
    {
        class Timer
        {
            public:
                Timer();
                virtual ~Timer();

                void Retart();
                // return time in ms(1 millisecond = 10e-3 second)
                double Time();
                // return time in ms(1 millisecond = 10e-3 second)
                float Timef();

            private:
				#ifdef USE_WINDOWS_TIME_QUERY
                double PC_freq_;
                uint64_t counter_start_;
				#else
                std::chrono::high_resolution_clock::time_point start_;
				#endif
        };
    }  // namespace Core

}  // namespace vEngine

#endif /* _VENGINE_CORE_TIMER_HPP */
