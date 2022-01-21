/// \file example_dll.cpp
/// \brief source file for class dll.
///
/// A detailed file description.
///
/// \author yuanli
/// \version 0.0.1
/// \date 2022-01-21

#include <iostream>
#include <vengine/core/example_dll.hpp>

/// only export function
/// should be 2 lines
int DLLClass::DLLFunc(int i)
{
    std::cout << "DLLClass" << std::endl;
    return i + 1;
}
int DLLClassFunc::DLLFunc(int i)
{
    std::cout << "DLLClassFunc" << std::endl;
    return i + 2;
}