#ifndef _INCLUDE_DEBUG_HPP
#define _INCLUDE_DEBUG_HPP

#pragma once

#ifdef VENGINE_PLATFORM_WINDOWS
    #define DEBUG_BREAK __debugbreak();
#else
    #include <signal.h>
    #define DEBUG_BREAK raise(SIGTRAP);
#endif

// debug and assert
#include <iostream>
#include <vengine/core/log.hpp>
#define VE_INFO(...) ::vEngine::Core::Log::GetInstance().Info(__VA_ARGS__);
#define VE_INFO_FILE_AND_FUCTION VE_INFO("in File ", __FILE__ , " Line " , __LINE__ , " Function " , __FUNCTION__)
#define VE_WARNING(...) ::vEngine::Core::Log::GetInstance().Warning(__VA_ARGS__);
#define VE_ERROR(...) ::vEngine::Core::Log::GetInstance().Error(__VA_ARGS__);

#define VE_ASSERT(condition, ...) if(!(condition)){VE_INFO( __VA_ARGS__);VE_INFO_FILE_AND_FUCTION;DEBUG_BREAK;}
#define VE_ASSERT_PTR_NOT_NULL(ptr, ...) if(ptr == nullptr){VE_INFO(__VA_ARGS__);VE_INFO_FILE_AND_FUCTION;DEBUG_BREAK;}
#define NOT_IMPL_ASSERT VE_INFO_FILE_AND_FUCTION; VE_ASSERT(false, "Assert: Not Implemented"); 

#define VE_STATIC_ASSERT(exp, x) static_assert(exp, x);           

#define DEBUG_CLASS_FILE_NAME              \
    virtual std::string GetName() override \
    {                                      \
        return __FILE__;                   \
    };
#define DEBUG_CLASS_NAME(x)                \
    virtual std::string GetName() override \
    {                                      \
        return x;                          \
    };

namespace vEngine
{
    class NotImplemented: public std::logic_error
    {
        public:
            NotImplemented() : std::logic_error("Not Implemented") {};
    };
}

#define NOT_IMPLEMENTED vEngine::NotImplemented not_implemented_exception;

#endif /* _INCLUDE_DEBUG_HPP */
