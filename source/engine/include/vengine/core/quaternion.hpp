/// \file quaternion.hpp
/// \brief Head file for Quaternion
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_QUATERNION_HPP
#define _VENGINE_CORE_QUATERNION_HPP

#pragma once

#include <engine.hpp>
#include <vengine/core/vector.hpp>
#include <vengine/core/math.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        /// \brief Quaternion for rotation
        ///
        /// real part of quaternion is x() component
        /// so Quaternion is (x, yi, zj, wk)
        template <typename T = float>
        class Quaternion final
        {
            private:
                typedef Vector<T, 4> DataType;
                DataType data_;

            public:
                // define types like std did
                typedef typename DataType::value_type value_type;

                typedef value_type* pointer;
                typedef const value_type* const_pointer;

                typedef typename DataType::reference reference;
                typedef typename DataType::const_reference const_reference;

                typedef typename DataType::iterator iterator;
                typedef typename DataType::const_iterator const_iterator;

                typedef typename DataType::size_type size_type;
                typedef typename DataType::difference_type difference_type;

            public:
             
                /// \brief Constructor: use init list {} to initialize data
                constexpr Quaternion() noexcept {}

                /// \brief Explicit one parameter constructor to avoid implicit conversion
                constexpr Quaternion(const T& other) noexcept = delete;
                constexpr Quaternion(const Vector<T>& other) noexcept = delete;

                /// \brief big five - 3: copy constructor
                ///
                /// copy constructor is called by \n
                ///  1. ClassA a = b; -> declear and assignment \n
                ///  2. Func(ClassA a) -> pass by value \n
                ///  3. return temp; -> return by value \n
                constexpr Quaternion(const Quaternion& other) noexcept
                {
                    this->data_ = other.data_;
                }

                /// \brief big five - 2: assignment operator
                ///
                /// with const formal paramter \n
                /// usage of constexpr: \n
                /// constexpr can not pass clang compiling => don't need constexpr as following \n
                /// constexpr Vector& operator=(const Vector& other) noexcept \n
                Quaternion& operator=(const Quaternion& other) noexcept
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
                constexpr Quaternion(Quaternion&& other) noexcept : data_(std::move(other.data_)) {}

                /// \brief big five - 5 : move operator
                ///
                /// move operator
                /// is used like unique_ptr
                constexpr Quaternion& operator=(const Quaternion&& other) noexcept
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
                constexpr Quaternion(const T* other) noexcept = delete;
                // {
                //     vector_t<T, N>::do_copy(this->data(), other);
                // }

                /// \brief copy from other vector type
                ///
                /// Will cast data type from U to T
                /// the size M should equal to N
                // template <typename U, int M>
                // constexpr Vector(Vector<U, M> const& rhs) noexcept
                // {
                //     static_assert(M == N);
                //     vector_t<T, N>::do_copy(this->data(), rhs.data());
                // }

                /// \brief init constructor
                ///
                /// use {} to init data, \n
                /// it will generate a compile error if
                /// vector is initd with more parameter than it has
                // constexpr Vector(const T& x, const T& y) noexcept : data_{x, y} {}
                // constexpr Vector(const T& x, const T& y, const T& z) noexcept : data_{x, y, z} {}
                constexpr Quaternion(const T& x, const T& y, const T& z, const T& w) noexcept : data_{x, y, z, w} {}


            public:
                iterator begin() noexcept
                {
                    return this->data_.begin();
                }
                const iterator begin() const noexcept
                {
                    return this->data_.begin();
                }

                iterator end() noexcept
                {
                    return this->data_.end();
                }
                const iterator end() const noexcept
                {
                    return this->data_.end();
                }

            public:
                reference x() noexcept
                {
                    return this->data_[0];
                }
                constexpr const_reference x() const noexcept
                {
                    return this->data_[0];
                }
                reference y() noexcept
                {
                    return this->data_[1];
                }
                constexpr const_reference y() const noexcept
                {
                    return this->data_[1];
                }
                reference z() noexcept
                {
                    return this->data_[2];
                }
                constexpr const_reference z() const noexcept
                {
                    return this->data_[2];
                }
                reference w() noexcept
                {
                    return this->data_[3];
                }
                constexpr const_reference w() const noexcept
                {
                    return this->data_[3];
                }
                pointer data() noexcept
                {
                    return &(this->data_[0]);
                }
                constexpr const_pointer data() const noexcept
                {
                    return &(this->data_[0]);
                }

                reference operator[](size_type index) noexcept
                {
                    return this->data_[index];
                }
                constexpr const_reference operator[](size_type index) const noexcept
                {
                    return this->data_[index];
                }

                public:
                // template<typename U>
                // const Quaternion& operator*=(const Quaternion<U>& other) noexcept
                // {
                //     return Math::Multiply(*this, other);
                // }
                template<typename U>
                const Quaternion<T> operator*(const Quaternion<U>& other) noexcept
                {
                    return Math::Multiply(*this, other);
                }


                void Norm();
                Quaternion<T> Conjugate()
                {
                    return Quaternion<T>(this->x(), -this->y(), -this->z(), -this->w());
                }
                void Inverse();

                public:

                static const Quaternion<T>& Identity()
                {
                    static Quaternion<T> identity(1,0,0,0);
                    return identity;
                }
        };
    }  // namespace Core
}  // namespace vEngine
#endif /* _VENGINE_CORE_QUATERNION_HPP */
