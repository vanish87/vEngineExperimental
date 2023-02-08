
/// \file shader.cpp
/// \brief source file for Shader
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <fstream>
#include <engine.hpp>
#include <vengine/rendering/shader.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Rendering
    {
        using namespace Core;

        /// constructor detailed defintion,
        /// should be 2 lines
        Shader::Shader(const GameObjectType type) : GameObject(type) {}

        /// A detailed function description, it
        /// should be 2 lines at least.
        int Shader::GetVariable(int p1, float p2)
        {
            UNUSED_PARAMETER(p1);
            UNUSED_PARAMETER(p2);
            return 1;
        }
    }  // namespace Rendering
}  // namespace vEngine
