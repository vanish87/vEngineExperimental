
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
                constexpr Vector(const Vector& other) {}

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
                virtual ~Vector() {}

                // big five - 4: move constructor
                // const is not need: constexpr Vector(const Vector &&other)
                // The move constructor:
                // - Takes an r-value reference as a parameter.
                // - Discards the object’s current state.
                // - Transfers ownership of the r-value object into the
                // receiver
                // - Puts the r-value object into an 'empty' state.
                // - subclass must explicitly std::move the base class
                constexpr Vector(Vector&& other) : data_{std::move(other.data_)}
                {
                    std::cout << "move ctor called" << std::endl;
                }
                // big five - 5 : move operator
                // is used like unique_ptr
                constexpr Vector& operator=(const Vector&& other)
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

                constexpr Vector(T x, T y) noexcept
                    : data_{std::move(x), std::move(y)}
                {}
        };

    }  // namespace Core
}  // namespace vEngine

#endif
