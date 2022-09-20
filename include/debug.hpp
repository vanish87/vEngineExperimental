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
// TODO Print colored warning with this
void WarningText(std::string text);
void ErrorText(std::string text);
#define PRINT(x) std::cout << x << std::endl;
#define PRINT_VAR(x)                      \
    std::cout << #x << ": " << std::endl; \
    x.Print();
#define PRINT_WARNING(x) WarningText(x);
#define PRINT_ERROR(x) ErrorText(x);
#define PRINT_AND_RETURN(x, returnVal) \
    {                                  \
        PRINT(x);                      \
        return returnVal;              \
    }
#define PRINT_FILE_AND_FUCTION PRINT("in File " << __FILE__ << " Line " << __LINE__ << " Function " << __FUNCTION__);
#define PRINT_AND_BREAK(x)      \
    {                           \
        PRINT(x);               \
        PRINT_FILE_AND_FUCTION; \
        DEBUG_BREAK             \
    }
#define CHECK_AND_ASSERT(condition, x) \
    {                                  \
        if (!(condition))              \
        {                              \
            PRINT(x);                  \
            PRINT_FILE_AND_FUCTION;    \
            DEBUG_BREAK                \
        }                              \
    }
#define CHECK_ASSERT_NOT_NULL(ptr)   \
    {                               \
        if (ptr == nullptr)         \
        {                           \
            PRINT_FILE_AND_FUCTION; \
            DEBUG_BREAK             \
        }                           \
    }

#define CHECK_ASSERT(condition)     \
    {                               \
        if (!(condition))           \
        {                           \
            PRINT_FILE_AND_FUCTION; \
            DEBUG_BREAK             \
        }                           \
    }
#define COMPILE_PRINT_AND_ASSERT(exp, x) \
    {                                    \
        static_assert(exp, x);           \
    }

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

#endif /* _INCLUDE_DEBUG_HPP */
