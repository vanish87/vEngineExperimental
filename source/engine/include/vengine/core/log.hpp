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
                // TODO: Use log tool/format/console gui for this
                std::cout<< first;
                Info(args...);
            }

            /// \brief A brief function description.
            void Info()
            {
                std::cout<<std::endl;
            }
            /// \brief A brief function description.
            ///
            /// \param p1 Description for p1.
            /// \param p2 Description for p2.
            /// \return Description for return value.
            template<typename T, typename... Args>
            void Warning(const T& first, const Args&... args) 
            {
                std::cout<< first;
                Warning(args...);
            }
            /// \brief A brief function description.
            void Warning()
            {
                std::cout<<std::endl;
                DEBUG_BREAK;
            }

            /// \brief A brief function description.
            ///
            /// \param p1 Description for p1.
            /// \param p2 Description for p2.
            /// \return Description for return value.
            template<typename T, typename... Args>
            void Error(const T& first, const Args&... args) 
            {
                std::cout<< first;
                Error(args...);
            }
            /// \brief A brief function description.
            void Error()
            {
                std::cout<<std::endl;
                DEBUG_BREAK;
            }
    };

}
    
}  // namespace MyNamespace

#endif /* _VENGINE_CORE_LOG_HPP */
