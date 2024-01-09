/// \file example_class.hpp
/// \brief Head file for class dll.
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_LOG_HPP
#define _VENGINE_CORE_LOG_HPP

#pragma once

#include <engine.hpp>

/// A brief namespace description.
namespace vEngine
{
    /// A brief namespace description.
    namespace Core
    {
    /// \brief A brief class description.
    ///
    /// A detailed class description, it
    /// should be 2 lines at least.
    class VENGINE_API Log
    {
        SINGLETON_CLASS(Log)

        public:
            /// \brief A brief function description.
            ///
            /// \param p1 Description for p1.
            /// \param p2 Description for p2.
            /// \return Description for return value.
            template<typename T, typename... Args>
            void Info(const T& first, const Args&... args) 
            {
                std::cout<< first;
                Info(args...);
            }

            void Info()
            {
                std::cout<<std::endl;
            }
            template<typename T, typename... Args>
            void Warning(const T& first, const Args&... args) 
            {
                std::cout<< first;
                Warning(args...);
            }
            void Warning()
            {
                std::cout<<std::endl;
            }
            template<typename T, typename... Args>
            void Error(const T& first, const Args&... args) 
            {
                std::cout<< first;
                Error(args...);
            }
            void Error()
            {
                std::cout<<std::endl;
            }
    };

}
    
}  // namespace MyNamespace

#endif /* _VENGINE_CORE_LOG_HPP */
