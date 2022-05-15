/// \file example_dll.hpp
/// \brief Head file for class dll.
///
/// A detailed file description.
///
/// \author yuanli
/// \version 0.0.1
/// \date 2022-01-21

#ifndef _VENGINE_CORE_EXAMPLE_DLL_HPP
#define _VENGINE_CORE_EXAMPLE_DLL_HPP

#pragma once
#include <VENGINE_API.hpp>

#include <engine.hpp>

/// \brief Export whole class to dll
///
/// A detailed class description, it
/// should be 2 lines at least.
class VENGINE_API DLLClass
{
    public:
        int i1;

    public:
        int DLLFunc(int i);
};

/// \brief Export class function to dll
///
/// A detailed class description, it
/// should be 2 lines at least.
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
