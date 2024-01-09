/// \file example_class.hpp
/// \brief Head file for class dll.
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_EVENT_HPP
#define _VENGINE_CORE_EVENT_HPP

#pragma once

#include "engine.hpp"

/// A brief namespace description.
namespace vEngine
{
    /// \brief A brief class description.
    ///
    /// A detailed class description, it
    /// should be 2 lines at least.
    class VENGINE_API Event
    {
        public:
            /// \brief brief constructor description.
            Event();

            /// class variable description
            int public_variable_;

        public:
            /// \brief A brief function description.
            ///
            /// \param p1 Description for p1.
            /// \param p2 Description for p2.
            /// \return Description for return value.
            int GetVariable(int p1, float p2);
    };

    /// \brief a brief C-Function description
    /// 
    /// \param para function paramter 1
    /// \return int function return value
    int CLikeFunction(int para);
    
}  // namespace MyNamespace



#endif /* _VENGINE_CORE_EVENT_HPP */
