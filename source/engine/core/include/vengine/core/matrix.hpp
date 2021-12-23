#ifndef _MATRIX4X4_HPP
#define _MATRIX4X4_HPP

#pragma once

#include <vengine/core/vector.hpp>
#include <vengine/core/math.h>

namespace vEngine
{
    namespace Math
    {
        /// \brief Define a MxN matrix with data type T
        /// 
        /// Note M is number of row elements, N is number of col elements. \n
        /// use matrix[row][col] to assess data. \n
        /// the data layout is colum major, see Math for details.
        /// \tparam T 
        /// \tparam M number of row elements
        /// \tparam N number of col elements
        template <typename T = float, int M = 4, int N = 4>
        class Matrix
        {
            private:
                typedef Vector<Vector<T, N>, M> DataType;

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

                static constexpr size_t size = M * N;
                static constexpr size_t row = M;
                static constexpr size_t col = N;

            public:
                // use init list {} to initialize data
                constexpr Matrix() noexcept {}

                // explicit one parameter constructor to avoid implicit
                // conversion
                explicit constexpr Matrix(const T& other) noexcept
                {
                    for (auto& r : this->data_)
                    {
                        vector_t<T, N>::do_assign(r.data(), other);
                    }
                }

                // big five - 3: copy constructor
                // called by
                //  1. ClassA a = b;
                //  2. Func(ClassA a) -> pass by value
                //  3. return temp; -> return by value
                constexpr Matrix(const Matrix& other) noexcept
                    : data_(other.data_)
                {
                    // vector_t<T, N>::do_copy(this->data(), other.data());
                }

                // big five - 2: assignment operator
                // with const formal paramter
                // with constexpr TODO: to clarify usage of constexpr
                // constexpr can not pass clang compiling => don't need it
                // constexpr Vector& operator=(const Vector& other) noexcept
                Matrix& operator=(const Matrix& other) noexcept
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
                // big five - 1: virtual destructor -> assure destructor of
                // subclass called
                virtual ~Matrix() noexcept {}

                // big five - 4: move constructor
                // const is not need: constexpr Vector(const Vector &&other)
                // The move constructor:
                // - Takes an r-value reference as a parameter.
                // - Discards the object’s current state.
                // - Transfers ownership of the r-value object into the
                // receiver
                // - Puts the r-value object into an 'empty' state.
                // - subclass must explicitly std::move the base class
                constexpr Matrix(Matrix&& other) noexcept
                    : data_(std::move(other.data_))
                {}
                // big five - 5 : move operator
                // is used like unique_ptr
                constexpr Matrix& operator=(const Matrix&& other) noexcept
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
                explicit constexpr Matrix(const T* other) noexcept
                {
                    for (auto& r : this->data_)
                    {
                        vector_t<T, N>::do_copy(r.data(), other);
                    }
                }

                // // copy from other matrix type
                // template <typename U, int M>
                // constexpr Matrix(Matrix<U, M> const& rhs) noexcept
                // {
                //     // vector_t<T, N>::do_copy(this->data(), rhs.data());
                // }

                // constexpr Matrix(const T& x, const T& y) noexcept : data_{x,
                // y}
                // {}

            public:
                static const Matrix<T, M, N>& Zero()
                {
                    static const Matrix<T, M, N> zero(0);
                    return zero;
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
                    return this->data_.begin() + size;
                }
                const iterator end() const noexcept
                {
                    return this->data_.begin() + size;
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

            public:
                template <typename U>
                const Matrix& operator+=(const Matrix<U, N>& other) noexcept
                {
                    for (auto r = 0; r < row; ++r)
                    {
                        this->data_[r] += other.data_[r];
                    }
                    return *this;
                }
                template <typename U>
                const Matrix& operator-=(const Matrix<U, N>& other) noexcept
                {
                    for (auto r = 0; r < row; ++r)
                    {
                        this->data_[r] -= other.data_[r];
                    }
                    return *this;
                }
                template <typename U>
                const Matrix& operator*=(const Matrix<U, N>& other) noexcept
                {
                    //ambiguous operator
                    assert(false);
                    return *this;
                }
                template <typename U>
                const Matrix& operator/=(const Matrix<U, N>& other) noexcept
                {
                    assert(false);
                    return *this;
                }
                constexpr Matrix const& operator+() const noexcept
                {
                    return *this;
                }
                Matrix const operator-() const noexcept
                {
                    Matrix ret;
                    for (auto r = 0; r < row; ++r)
                    {
                        ret.data_[r] = -this->data_[r];
                    }
                    return ret;
                }

                bool operator==(const Matrix& other) const noexcept
                {
                    for (auto r = 0; r < row; ++r)
                    {
                        if(this->data_[r] != other.data_[r]) return false;
                    }
                    return true;
                }

                // Boost defined operator
            public:
                template <typename U>
                constexpr Matrix operator+(Matrix<U, M, N>& other) noexcept
                {
                    return Matrix(*this) += other;
                }
                template <typename U>
                constexpr Matrix operator-(Matrix<U, M, N>& other) noexcept
                {
                    return Matrix(*this) -= other;
                }
                template <typename U>
                constexpr Matrix operator*(Matrix<U, M, N>& other) noexcept
                {
                    return Multiply(*this, other);
                }
                template <typename U>
                constexpr Matrix operator/(Matrix<U, M, N>& other) noexcept
                {
                    return Matrix(*this) /= other;
                }
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _MATRIX4X4_HPP */
