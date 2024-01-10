/// \file example_class.cpp
/// \brief source file for class example.
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/event.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{

    /// constructor detailed defintion,
    /// should be 2 lines
    Event::Event() : public_variable_(10) {}

    /// A detailed function description, it
    /// should be 2 lines at least.
    int Event::GetVariable(int p1, float p2)
    {
        UNUSED_PARAMETER(p1);
        UNUSED_PARAMETER(p2);
        return 1;
    }

    /// A detailed c-function description, it
    /// should be 2 lines at least.
    int CLikeFunction(int para)
    {
        return para++;
    }
}  // namespace MyNamespace