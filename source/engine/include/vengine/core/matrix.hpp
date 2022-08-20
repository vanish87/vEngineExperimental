#ifndef _VENGINE_CORE_MATRIX_HPP
#define _VENGINE_CORE_MATRIX_HPP

#pragma once
#include <vengine/core/math.hpp>

// #include <engine.hpp>
#include <vengine/core/vector.hpp>

namespace vEngine
{
    namespace Core
    {
        enum class MatrixPackType
        {
            ColumnMajor, //default
            RowMajor
        };
        /// \brief Define a MxN matrix with data type T
        ///
        /// Note M is the number of row elements, N is the number of col elements. \n
        /// use matrix[row][col] to assess data. \n
        /// the data layout is colum major, see Math for details.
        /// \tparam T
        /// \tparam M number of row elements
        /// \tparam N number of col elements
        template <typename T = float, int M = 4, int N = 4>
        class VENGINE_API Matrix final
        {
            private:
                typedef Vector<Vector<T, M>, N> DataType;

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

                static constexpr size_type size = M * N;
                static constexpr size_type row = N;
                static constexpr size_type col = M;

                static const MatrixPackType PackType = MatrixPackType::RowMajor;

            public:
                constexpr Matrix() noexcept {}

                /// \brief Init constructor for matrix
                constexpr Matrix(T m00, T m01, T m02, T m03, 
                                 T m10, T m11, T m12, T m13, 
                                 T m20, T m21, T m22, T m23,
                                 T m30, T m31, T m32, T m33) noexcept
                {
                    static_assert(M == 4);
                    static_assert(N == 4);

                    this->data_[0][0] = std::move(m00);
                    this->data_[0][1] = std::move(m01);
                    this->data_[0][2] = std::move(m02);
                    this->data_[0][3] = std::move(m03);

                    this->data_[1][0] = std::move(m10);
                    this->data_[1][1] = std::move(m11);
                    this->data_[1][2] = std::move(m12);
                    this->data_[1][3] = std::move(m13);

                    this->data_[2][0] = std::move(m20);
                    this->data_[2][1] = std::move(m21);
                    this->data_[2][2] = std::move(m22);
                    this->data_[2][3] = std::move(m23);

                    this->data_[3][0] = std::move(m30);
                    this->data_[3][1] = std::move(m31);
                    this->data_[3][2] = std::move(m32);
                    this->data_[3][3] = std::move(m33);
                }

                // explicit one parameter constructor to avoid implicit
                // conversion
                explicit constexpr Matrix(const T& other) noexcept
                {
                    for (auto& r : this->data_)
                    {
                        vector_t<T, col>::do_assign(r.data(), other);
                    }
                }
                // explicit constexpr Matrix(const Vector<T, M>& other) noexcept
                // {
                //     static_assert(N == 1);

                //     for (auto& r : this->data_)
                //     {
                //         vector_t<T, N>::do_assign(r.data(), other);
                //     }
                // }

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
                ~Matrix() noexcept {}

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

                // constructor obj with pointer
                explicit constexpr Matrix(const T* other) noexcept
                {
                    for (auto& r : this->data_)
                    {
                        vector_t<T, col>::do_copy(r.data(), other);
                    }
                }


            public:
                static const Matrix<T, M, N>& Zero()
                {
                    static const T z(0);
                    static const Matrix<T, M, N> zero(z);
                    return zero;
                }
                static const Matrix<T, M, N>& Identity()
                {
                    static Matrix<T, M, N> identity;
                    Math::Identity(identity);
                    return identity;
                }

            public:
                iterator begin() noexcept
                {
                    return this->data_.begin();
                }
                const_iterator begin() const noexcept
                {
                    return this->data_.begin();
                }

                iterator end() noexcept
                {
                    return this->data_.end();
                }
                const_iterator end() const noexcept
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
                    return this->data_[index];
                }
                constexpr const_reference operator[](
                    size_type index) const noexcept
                {
                    return this->data_[index];
                }

            public:
                template <typename U>
                const Matrix& operator+=(const Matrix<U, N>& other) noexcept
                {
                    for (size_type r = 0; r < row; ++r)
                    {
                        this->data_[r] += other.data_[r];
                    }
                    return *this;
                }
                template <typename U>
                const Matrix& operator-=(const Matrix<U, N>& other) noexcept
                {
                    for (size_type r = 0; r < row; ++r)
                    {
                        this->data_[r] -= other.data_[r];
                    }
                    return *this;
                }
                // ambiguous operator
                template <typename U>
                const Matrix& operator*=(const Matrix<U, N>& other) noexcept
                {
                    UNUSED_PARAMETER(other);
                    // assert(false);
                    return *this;
                }
                // ambiguous operator
                template <typename U>
                const Matrix& operator/=(const Matrix<U, N>& other) noexcept
                {
                    UNUSED_PARAMETER(other);
                    // assert(false);
                    return *this;
                }
                constexpr Matrix const& operator+() const noexcept
                {
                    return *this;
                }
                Matrix const operator-() const noexcept
                {
                    Matrix ret;
                    for (size_type r = 0; r < row; ++r)
                    {
                        ret.data_[r] = -this->data_[r];
                    }
                    return ret;
                }

                bool operator==(const Matrix& other) const noexcept
                {
                    for (size_type r = 0; r < row; ++r)
                    {
                        if (this->data_[r] != other.data_[r]) return false;
                    }
                    return true;
                }

                // Boost defined operator
            public:
                template <typename U>
                constexpr Matrix operator+(const Matrix<U, M, N>& other) noexcept
                {
                    return Matrix(*this) += other;
                }
                template <typename U>
                constexpr Matrix operator-(const Matrix<U, M, N>& other) noexcept
                {
                    return Matrix(*this) -= other;
                }
                template <typename U>
                constexpr Matrix operator*(const Matrix<U, M, N>& other) noexcept
                {
                    return Math::Multiply(*this, other);
                }
                template <typename U>
                constexpr Matrix operator/(const Matrix<U, M, N>& other) noexcept
                {
                    return Matrix(*this) /= other;
                }
        };

    }  // namespace Math
}  // namespace vEngine

#endif /* _VENGINE_CORE_MATRIX_HPP */