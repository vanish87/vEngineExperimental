/// \file example_class.hpp
/// \brief Head file for class dll.
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_EXAMPLE_CLASS_HEADER_H
#define _VENGINE_CORE_EXAMPLE_CLASS_HEADER_H

#pragma once

/// A brief namespace description.
namespace MyNamespace
{
    /// \brief A brief class description.
    ///
    /// A detailed class description, it
    /// should be 2 lines at least.
    class MyClass
    {
        public:
            /// \brief brief constructor description.
            MyClass();

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

#endif /* _VENGINE_CORE_EXAMPLE_CLASS_HEADER_H */
