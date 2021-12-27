#include <iostream>
#include <vengine/core/example_dll.hpp>

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