
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
        template<typename T = float>
        class Radian
        {
            private:
                typedef T DataType;
                DataType data_;

            public:
                /// \brief brief constructor description.
                constexpr Radian() noexcept {}

                /// \brief Explicit one parameter constructor to avoid implicit conversion
                explicit constexpr Radian(const T& other) noexcept
                : data_{other} // this only assign first element
                {

                }

                /// \brief big five - 3: copy constructor
                ///
                /// copy constructor is called by \n
                ///  1. ClassA a = b; -> declear and assignment \n
                ///  2. Func(ClassA a) -> pass by value \n
                ///  3. return temp; -> return by value \n
                constexpr Radian(const Radian& other) noexcept
                :data_{other.data_}
                {
                }

                /// \brief big five - 2: assignment operator
                ///
                /// with const formal paramter \n
                /// usage of constexpr: \n
                /// constexpr can not pass clang compiling => don't need constexpr as following \n
                /// constexpr Vector& operator=(const Vector& other) noexcept \n
                Radian& operator=(const Radian& other) noexcept
                {
                    // 1.check self assignment
                    if (this != &other)
                    {
                        // 2.allocate new object before-> to assure memory
                        // before delete existing one
                        this->data_ = other.data_;
                    }
                    return *this;
                }

                /// \brief big five - 1: virtual destructor
                ///
                /// to assure destructor of
                /// subclass called
                /// do not need for vector class
                // virtual ~Vector() noexcept {}

                /// \brief big five - 4: move constructor
                ///
                /// const is not needed: constexpr Vector(const Vector &&other) \n
                /// The move constructor: \n
                /// - Takes an r-value reference as a parameter. \n
                /// - Discards the object’s current state. \n
                /// - Transfers ownership of the r-value object into the receiver \n
                /// - Puts the r-value object into an 'empty' state. \n
                /// - subclass must explicitly std::move the base class \n
                constexpr Radian(Radian&& other) noexcept : data_(std::move(other.data_)) {}

                /// \brief big five - 5 : move operator
                ///
                /// move operator
                /// is used like unique_ptr
                constexpr Radian& operator=(const Radian&& other) noexcept
                {
                    // 1.check self assignment
                    if (this != &other)
                    {
                        // 2.allocate new object before-> to assure memory
                        // before delete existing one
                        this->data_ = std::move(other.data_);
                    }
                    return *this;
                }

                /// \brief constructor vector with pointer
                ///
                /// Usually used to init vector with
                /// a data array
                explicit constexpr Radian(const T* other) noexcept
                {
                    this->data_ = &other;
                }

                /// \brief copy from other vector type
                ///
                /// Will cast data type from U to T
                /// the size M should equal to N
                template <typename U>
                constexpr Radian(Radian<U> const& rhs) noexcept
                {
                    this->data_ = static_cast<T>(rhs.data_);
                }
        };
        template<typename T = float>
        class Degree
        {
            private:
                typedef T DataType;
                DataType data_;

            public:
                /// \brief brief constructor description.
                constexpr Degree() noexcept {}

                /// \brief Explicit one parameter constructor to avoid implicit conversion
                explicit constexpr Degree(const T& other) noexcept
                : data_{other} // this only assign first element
                {

                }

                /// \brief big five - 3: copy constructor
                ///
                /// copy constructor is called by \n
                ///  1. ClassA a = b; -> declear and assignment \n
                ///  2. Func(ClassA a) -> pass by value \n
                ///  3. return temp; -> return by value \n
                constexpr Degree(const Degree& other) noexcept
                :data_{other.data_}
                {
                }

                /// \brief big five - 2: assignment operator
                ///
                /// with const formal paramter \n
                /// usage of constexpr: \n
                /// constexpr can not pass clang compiling => don't need constexpr as following \n
                /// constexpr Vector& operator=(const Vector& other) noexcept \n
                Degree& operator=(const Degree& other) noexcept
                {
                    // 1.check self assignment
                    if (this != &other)
                    {
                        // 2.allocate new object before-> to assure memory
                        // before delete existing one
                        this->data_ = other.data_;
                    }
                    return *this;
                }

                /// \brief big five - 1: virtual destructor
                ///
                /// to assure destructor of
                /// subclass called
                /// do not need for vector class
                // virtual ~Vector() noexcept {}

                /// \brief big five - 4: move constructor
                ///
                /// const is not needed: constexpr Vector(const Vector &&other) \n
                /// The move constructor: \n
                /// - Takes an r-value reference as a parameter. \n
                /// - Discards the object’s current state. \n
                /// - Transfers ownership of the r-value object into the receiver \n
                /// - Puts the r-value object into an 'empty' state. \n
                /// - subclass must explicitly std::move the base class \n
                constexpr Degree(Degree&& other) noexcept : data_(std::move(other.data_)) {}

                /// \brief big five - 5 : move operator
                ///
                /// move operator
                /// is used like unique_ptr
                constexpr Degree& operator=(const Degree&& other) noexcept
                {
                    // 1.check self assignment
                    if (this != &other)
                    {
                        // 2.allocate new object before-> to assure memory
                        // before delete existing one
                        this->data_ = std::move(other.data_);
                    }
                    return *this;
                }

                /// \brief constructor vector with pointer
                ///
                /// Usually used to init vector with
                /// a data array
                explicit constexpr Degree(const T* other) noexcept
                {
                    this->data_ = &other;
                }

                /// \brief copy from other vector type
                ///
                /// Will cast data type from U to T
                /// the size M should equal to N
                template <typename U>
                constexpr Degree(Degree<U> const& rhs) noexcept
                {
                    this->data_ = static_cast<T>(rhs.data_);
                }
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_ANGLE_HPP */
