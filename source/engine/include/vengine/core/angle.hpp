
/// \file example_class.hpp
/// \brief Head file for class dll.
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_ANGLE_HPP
#define _VENGINE_CORE_ANGLE_HPP

#pragma once

#include <engine.hpp>

/// A brief namespace description.
namespace vEngine
{
    /// \brief A brief class description.
    ///
    /// A detailed class description, it
    /// should be 2 lines at least.
    namespace Core
    {
        class Radian
        {
            public:
                /// \brief brief constructor description.
                Radian();
        };
        class Degree
        {
            private:
                int16_t data_;
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_ANGLE_HPP */
