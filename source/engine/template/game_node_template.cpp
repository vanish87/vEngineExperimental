/// \file game_node_template.cpp
/// \brief source file for Game Node template
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/game_node_template.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {

        /// constructor detailed defintion,
        /// should be 2 lines
        GameNodeTemplate::GameNodeTemplate() {}
        GameNodeTemplate::~GameNodeTemplate() {}

        /// A detailed function description, it
        /// should be 2 lines at least.
        int MyClass::GetVariable(int p1, float p2)
        {
            UNUSED_PARAMETER(p1);
            UNUSED_PARAMETER(p2);
            return 1;
        }

    }  // namespace Core
}  // namespace vEngine