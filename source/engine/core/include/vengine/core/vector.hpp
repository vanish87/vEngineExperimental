
#ifndef VECTOR_H
#define VECTOR_H

#pragma once

#include <array>
#include <iostream>

namespace vEngine
{
    namespace Core
    {
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
                constexpr Vector() noexcept : data_{0} {}

                // explicit one parameter constructor to avoid implicit
                // conversion
                explicit constexpr Vector(const T& other) noexcept {}

                // big five - 3: copy constructor
                // called by
                //  1. ClassA a = b;
                //  2. Func(ClassA a) -> pass by value
                //  3. return temp; -> return by value
                constexpr Vector(const Vector& other) noexcept {}

                // big five - 2: assignment operator
                // with const formal paramter
                // with constexpr TODO: to clarify usage of constexpr
                // constexpr can not pass clang compiling => don't need it
                constexpr Vector& operator=(const Vector& other) noexcept
                {
                    // 1.check self assignment
                    if (this != &other)
                    {
                        // 2.allocate new object before-> to assure memory
                        // before delete existing one
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
                    : data_{std::move(other.data_)}
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
                    }
                    return *this;
                }

                // ambiguous/undefined actions
                // constructor obj with pointer
                explicit constexpr Vector(const T* other) noexcept {}

                // copy from other vector type
                template <typename U, int M>
                constexpr Vector(Vector<U, M> const& rhs) noexcept
                {}

                constexpr Vector(const T& x, const T& y) noexcept : data_{x, y}
                {}

            public:
                static const Vector<T, N>& Zero()
                {
                    static const Vector<T, N> zero(static_cast<T>(0));
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
                    return this->data_[index];
                }
                constexpr const_reference operator[](
                    size_t index) const noexcept
                {
                    return this->data_[index];
                }

                // TODO: use vector swizzle
                reference x() noexcept
                {
                    return this->data_[0];
                }

            public:
                template <typename U>
                const Vector& operator+=(const Vector<U, N>& other) noexcept
                {
                    return *this;
                }
                template <typename U>
                const Vector& operator-=(const Vector<U, N>& other) noexcept
                {
                    return *this;
                }
                template <typename U>
                const Vector& operator*=(const Vector<U, N>& other) noexcept
                {
                    return *this;
                }
                template <typename U>
                const Vector& operator/=(const Vector<U, N>& other) noexcept
                {
                    return *this;
                }
                constexpr Vector const& operator+() const noexcept
                {
                    return *this;
                }
                Vector const operator-() const noexcept
                {
                    return *this;
                }

                bool operator==(const Vector& other) const noexcept
                {
                    return true;
                }

            // Boost defined operator
            public:
                template <typename U>
                constexpr Vector operator+(Vector<U, N>& other) noexcept
                {
                    return *this;
                }
                template <typename U>
                constexpr Vector operator-(Vector<U, N>& other) noexcept
                {
                    return *this;
                }
                template <typename U>
                constexpr Vector operator*(Vector<U, N>& other) noexcept
                {
                    return *this;
                }
                template <typename U>
                constexpr Vector operator/(Vector<U, N>& other) noexcept
                {
                    return *this;
                }
        };
        template <typename T, int N>
        inline void swap(Vector<T, N>& lhs, Vector<T, N>& other) noexcept
        {}

    }  // namespace Core
}  // namespace vEngine

#endif