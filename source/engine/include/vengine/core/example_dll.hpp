#ifndef _VENGINE_CORE_EXAMPLE_DLL_HPP
#define _VENGINE_CORE_EXAMPLE_DLL_HPP

#pragma once
#include <VENGINE_API.h>

#include <engine.hpp>

class VENGINE_API DLLClass
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
        VENGINE_API int DLLFunc(int i);
        VENGINE_API int DLLFunc1(int i)
        {
            UNUSED_PARAMETER(i);
            return 0;
        };
};

#endif /* _VENGINE_CORE_EXAMPLE_DLL_HPP */
