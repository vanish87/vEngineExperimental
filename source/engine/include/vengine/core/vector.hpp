/// \file vector.hpp
/// \brief Head file for vector
///
/// Vector implentation
///
/// \author yuanli
/// \version 0.0.1
/// \date 2022-01-21

#ifndef _VENGINE_CORE_VECTOR_HPP
#define _VENGINE_CORE_VECTOR_HPP

#pragma once
#include <array>
#include <engine.hpp>
#include <vengine/core/template_helper.hpp>

namespace vEngine
{
    namespace Core
    {
        /// \brief Basic vector data type
        ///
        /// Use std::array to store data,
        /// Use template recrusion for compile time calculation
        /// \tparam T Vector type
        /// \tparam N Vector size
        template <typename T = float, int N = 4>
        class Vector final
        {
            private:
                typedef std::array<T, N> DataType;

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

                static constexpr size_type size = N;
                static constexpr size_type byte_size = N * sizeof(value_type);

            public:
                /// \brief Constructor: use init list {} to initialize data
                constexpr Vector() noexcept {}

                /// \brief Explicit one parameter constructor to avoid implicit conversion
                explicit constexpr Vector(const T& other) noexcept
                // : data_{other} // this only assign first element
                {
                    vector_t<T, N>::do_assign(this->data(), other);
                }

                /// \brief big five - 3: copy constructor
                ///
                /// copy constructor is called by \n
                ///  1. ClassA a = b; -> declear and assignment \n
                ///  2. Func(ClassA a) -> pass by value \n
                ///  3. return temp; -> return by value \n
                constexpr Vector(const Vector& other) noexcept
                {
                    vector_t<T, N>::do_copy(this->data(), other.data());
                }

                /// \brief big five - 2: assignment operator
                ///
                /// with const formal paramter \n
                /// usage of constexpr: \n
                /// constexpr can not pass clang compiling => don't need constexpr as following \n
                /// constexpr Vector& operator=(const Vector& other) noexcept \n
                Vector& operator=(const Vector& other) noexcept
                {
                    // 1.check self assignment
                    if (this != &other)
                    {
                        // 2.allocate new object before-> to assure memory
                        // before delete existing one
                        vector_t<T, N>::do_assign(this->data(), other.data());
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
                constexpr Vector(Vector&& other) noexcept : data_(std::move(other.data_)) {}

                /// \brief big five - 5 : move operator
                ///
                /// move operator
                /// is used like unique_ptr
                constexpr Vector& operator=(const Vector&& other) noexcept
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
                explicit constexpr Vector(const T* other) noexcept
                {
                    vector_t<T, N>::do_copy(this->data(), other);
                }

                /// \brief copy from other vector type
                ///
                /// Will cast data type from U to T
                /// the size M should equal to N
                template <typename U, int M>
                constexpr Vector(Vector<U, M> const& rhs) noexcept
                {
                    static_assert(M == N);
                    vector_t<T, N>::do_copy(this->data(), rhs.data());
                }

                /// \brief init constructor
                ///
                /// use {} to init data, \n
                /// it will generate a compile error if
                /// vector is initd with more parameter than it has
                constexpr Vector(const T& x, const T& y) noexcept : data_{x, y} {}
                constexpr Vector(const T& x, const T& y, const T& z) noexcept : data_{x, y, z} {}
                constexpr Vector(const T& x, const T& y, const T& z, const T& w) noexcept : data_{x, y, z, w} {}

            public:
                /// \brief static all 0 vector
                static const Vector<T, N>& Zero()
                {
                    static const Vector<T, N> zero(T(0));
                    return zero;
                }
                /// \brief static all 1 vector
                static const Vector<T, N>& One()
                {
                    static const Vector<T, N> one{1};
                    return one;
                }

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
                    CHECK_ASSERT(index < N);
                    return this->data_[index];
                }
                constexpr const_reference operator[](size_type index) const noexcept
                {
                    CHECK_ASSERT(index < N);
                    return this->data_[index];
                }

                // TODO: use vector swizzle
                // https://zhuanlan.zhihu.com/p/29618817
                reference x() noexcept
                {
                    return this->data_[0];
                }
                reference y() noexcept
                {
                    static_assert(size > 1);
                    return this->data_[1];
                }
                reference z() noexcept
                {
                    static_assert(size > 2);
                    return this->data_[2];
                }
                reference w() noexcept
                {
                    static_assert(size > 3);
                    return this->data_[3];
                }

                const_reference x() const noexcept
                {
                    return this->data_[0];
                }
                const_reference y() const noexcept
                {
                    static_assert(size > 1);
                    return this->data_[1];
                }
                const_reference z() const noexcept
                {
                    static_assert(size > 2);
                    return this->data_[2];
                }
                const_reference w() const noexcept
                {
                    static_assert(size > 3);
                    return this->data_[3];
                }

            public:
                /// \brief add each element of vector
                template <typename U>
                const Vector& operator+=(const Vector<U, N>& other) noexcept
                {
                    vector_t<T, N>::do_add(this->data(), this->data(), other.data());
                    return *this;
                }
                /// \brief substract each element of vector
                template <typename U>
                const Vector& operator-=(const Vector<U, N>& other) noexcept
                {
                    vector_t<T, N>::do_sub(this->data(), this->data(), other.data());
                    return *this;
                }
                /// \brief multiply each element of vector
                template <typename U>
                const Vector& operator*=(const Vector<U, N>& other) noexcept
                {
                    vector_t<T, N>::do_mul(this->data(), this->data(), other.data());
                    return *this;
                }
                /// \brief scale each element of vector
                template <typename U>
                const Vector& operator*=(const U& other) noexcept
                {
                    vector_t<T, N>::do_mul(this->data(), this->data(), other);
                    return *this;
                }
                /// \brief divide each element of vector
                template <typename U>
                const Vector& operator/=(const Vector<U, N>& other) noexcept
                {
                    vector_t<T, N>::do_div(this->data(), this->data(), other.data());
                    return *this;
                }
                /// \brief take it self positive
                constexpr Vector const& operator+() const noexcept
                {
                    return *this;
                }
                /// \brief nagenate vector
                Vector const operator-() const noexcept
                {
                    Vector ret;
                    vector_t<T, N>::do_negative(ret.data(), this->data());
                    return ret;
                }

                /// \brief conpare all element of vector
                bool operator==(const Vector& other) const noexcept
                {
                    return vector_t<T, N>::do_equal(this->data(), other.data());
                }
                /// \brief conpare all element of vector
                bool operator!=(const Vector& other) const noexcept
                {
                    return !(*this == other);
                }

            public:
                // Boost defined operator
                template <typename U>
                constexpr Vector operator+(const Vector<U, N>& other) const noexcept
                {
                    return Vector(*this) += other;
                }
                template <typename U>
                constexpr Vector operator-(const Vector<U, N>& other) const noexcept
                {
                    return Vector(*this) -= other;
                }
                template <typename U>
                constexpr Vector operator*(const Vector<U, N>& other) const noexcept
                {
                    return Vector(*this) *= other;
                }
                template <typename U>
                constexpr Vector operator*(const U& other) const noexcept
                {
                    return Vector(*this) *= other;
                }
                template <typename U>
                constexpr Vector operator/(const Vector<U, N>& other) const noexcept
                {
                    return Vector(*this) /= other;
                }
        };
        /// \brief swap two vectors
        template <typename T, int N>
        inline void swap(Vector<T, N>& lhs, Vector<T, N>& rhs) noexcept
        {
            return vector_t<T, N>::do_swap(lhs.data(), rhs.data());
        }
    }  // namespace Math
}  // namespace vEngine

#endif /* _VENGINE_CORE_VECTOR_HPP */
