/// \file example_class.cpp
/// \brief source file for class Ctest.
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/example_class_header.h>

#include <engine.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace MyNamespace
{

    /// constructor detailed defintion,
    /// should be 2 lines
    MyClass::MyClass() : PublicVariable(10) {}

    /// A detailed function description, it
    /// should be 2 lines at least.
    int MyClass::GetVariable(int p1, float p2)
    {
        UNUSED_PARAMETER(p1);
        UNUSED_PARAMETER(p2);
        return 1;
    }
}  // namespace MyNamespace