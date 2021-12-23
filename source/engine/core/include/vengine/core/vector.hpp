
#ifndef VECTOR_H
#define VECTOR_H

#pragma once

#include <array>
#include <iostream>
#include <vengine/core/template_helper.hpp>
#include <vengine/core/debug.hpp>

namespace vEngine
{
    namespace Math
    {
        // basic data type will be static linked to main app
        // so no CORE_API here
        // plugin etc. will generate dll using CORE_API.h
        template <typename T = float, int N = 4>
        class Vector
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

                static constexpr size_t size = N;

            public:
                // use init list {} to initialize data
                constexpr Vector() noexcept {}

                // explicit one parameter constructor to avoid implicit
                // conversion
                explicit constexpr Vector(const T& other) noexcept
                // : data_{other} // this only assign first element
                {
                    vector_t<T, N>::do_assign(this->data(), other);
                }

                // big five - 3: copy constructor
                // called by
                //  1. ClassA a = b;
                //  2. Func(ClassA a) -> pass by value
                //  3. return temp; -> return by value
                constexpr Vector(const Vector& other) noexcept
                {
                    vector_t<T, N>::do_copy(this->data(), other.data());
                }

                // big five - 2: assignment operator
                // with const formal paramter
                // with constexpr TODO: to clarify usage of constexpr
                // constexpr can not pass clang compiling => don't need it
                // constexpr Vector& operator=(const Vector& other) noexcept
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
                // big five - 1: virtual destructor -> assure destructor of
                // subclass called
                virtual ~Vector() noexcept {}

                // big five - 4: move constructor
                // const is not need: constexpr Vector(const Vector &&other)
                // The move constructor:
                // - Takes an r-value reference as a parameter.
                // - Discards the object’s current state.
                // - Transfers ownership of the r-value object into the
                // receiver
                // - Puts the r-value object into an 'empty' state.
                // - subclass must explicitly std::move the base class
                constexpr Vector(Vector&& other) noexcept
                    : data_(std::move(other.data_))
                {}
                // big five - 5 : move operator
                // is used like unique_ptr
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

                // ambiguous/undefined actions
                // constructor obj with pointer
                explicit constexpr Vector(const T* other) noexcept
                {
                    vector_t<T, N>::do_copy(this->data(), other);
                }

                // copy from other vector type
                template <typename U, int M>
                constexpr Vector(Vector<U, M> const& rhs) noexcept
                {
                    vector_t<T, N>::do_copy(this->data(), rhs.data());
                }

                constexpr Vector(const T& x, const T& y) noexcept : data_{x, y}
                {}
                constexpr Vector(const T& x, const T& y, const T& z) noexcept
                    : data_{x, y, z}
                {}
                constexpr Vector(const T& x, const T& y, const T& z,
                                 const T& w) noexcept
                    : data_{x, y, z, w}
                {}

            public:
                static const Vector<T, N>& Zero()
                {
                    static const Vector<T, N> zero(T(0));
                    return zero;
                }
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

                reference operator[](size_t index) noexcept
                {
                    CHECK_ASSERT(index < N);
                    return this->data_[index];
                }
                constexpr const_reference operator[](
                    size_t index) const noexcept
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
                    return this->data_[1];
                }
                reference z() noexcept
                {
                    return this->data_[2];
                }
                reference w() noexcept
                {
                    return this->data_[3];
                }

                const_reference x() const noexcept
                {
                    return this->data_[0];
                }
                const_reference y() const noexcept
                {
                    return this->data_[1];
                }
                const_reference z() const noexcept
                {
                    return this->data_[2];
                }
                const_reference w() const noexcept
                {
                    return this->data_[3];
                }

            public:
                template <typename U>
                const Vector& operator+=(const Vector<U, N>& other) noexcept
                {
                    vector_t<T, N>::do_add(this->data(), this->data(),
                                           other.data());
                    return *this;
                }
                template <typename U>
                const Vector& operator-=(const Vector<U, N>& other) noexcept
                {
                    vector_t<T, N>::do_sub(this->data(), this->data(),
                                           other.data());
                    return *this;
                }
                template <typename U>
                const Vector& operator*=(const Vector<U, N>& other) noexcept
                {
                    vector_t<T, N>::do_mul(this->data(), this->data(),
                                           other.data());
                    return *this;
                }
                template <typename U>
                const Vector& operator*=(const U& other) noexcept
                {
                    vector_t<T, N>::do_mul(this->data(), this->data(),
                                           other);
                    return *this;
                }
                template <typename U>
                const Vector& operator/=(const Vector<U, N>& other) noexcept
                {
                    vector_t<T, N>::do_div(this->data(), this->data(),
                                           other.data());
                    return *this;
                }
                constexpr Vector const& operator+() const noexcept
                {
                    return *this;
                }
                Vector const operator-() const noexcept
                {
                    Vector ret;
                    vector_t<T, N>::do_negative(ret.data(), this->data());
                    return ret;
                }

                bool operator==(const Vector& other) const noexcept
                {
                    return vector_t<T, N>::do_equal(this->data(), other.data());
                }
                bool operator!=(const Vector& other) const noexcept
                {
                    return !(*this == other);
                }

                // Boost defined operator
            public:
                template <typename U>
                constexpr Vector operator+(const Vector<U, N>& other) noexcept
                {
                    return Vector(*this) += other;
                }
                template <typename U>
                constexpr Vector operator-(const Vector<U, N>& other) noexcept
                {
                    return Vector(*this) -= other;
                }
                template <typename U>
                constexpr Vector operator*(const Vector<U, N>& other) noexcept
                {
                    return Vector(*this) *= other;
                }
                // TODO: ambiguous multiply function, use scale
                template <typename U>
                constexpr Vector operator*(const U& other) noexcept
                {
                    return Vector(*this) *= other;
                }
                template <typename U>
                constexpr Vector operator*(const U& other) const noexcept
                {
                    return Vector(*this) *= other;
                }
                template <typename U>
                constexpr Vector operator/(const Vector<U, N>& other) noexcept
                {
                    return Vector(*this) /= other;
                }
        };
        template <typename T, int N>
        inline void swap(Vector<T, N>& lhs, Vector<T, N>& rhs) noexcept
        {
            return vector_t<T, N>::do_swap(lhs.data(), rhs.data());
        }
    }  // namespace Core
}  // namespace vEngine

#endif
