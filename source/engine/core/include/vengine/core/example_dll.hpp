#ifndef _VENGINE_CORE_EXAMPLE_DLL_HPP
#define _VENGINE_CORE_EXAMPLE_DLL_HPP

#pragma once
#include <CORE_API.h>

#include <engine.hpp>

class CORE_API DLLClass
{
    public:
        int i1;

    public:
        int DLLFunc(int i);
};

class DLLClassFunc
{
    public:
        int i1;

    public:
        CORE_API int DLLFunc(int i);
        CORE_API int DLLFunc1(int i)
        {
            UNUSED_PARAMETER(i);
            return 0;
        };
};

#endif /* _VENGINE_CORE_EXAMPLE_DLL_HPP */
