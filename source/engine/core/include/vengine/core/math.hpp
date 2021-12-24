#ifndef _VENGINE_MATH_HPP
#define _VENGINE_MATH_HPP

#pragma once

#include <vengine/core/debug.hpp>

namespace vEngine
{
    namespace Math
    {
        /// Detailed function doc
        template <typename T>
        bool IsNAN(const T& x)
        {
            return std::isnan(x);
        }

        template <typename T>
        bool IsINF(const T& x)
        {
            return std::isinf(x);
        }

        template <typename T>
        T Min(const T& lhs, const T& rhs)
        {
            return std::min(lhs, rhs);
        }
        template <typename T>
        T Max(const T& lhs, const T& rhs)
        {
            return std::max(lhs, rhs);
        }

        template <typename T>
        T Clamp(const T& value, const T& min, const T& max)
        {
            return value < min ? min : value > max ? max : value;
        }
        template <typename T, int N>
        void Identity(Matrix<T, N, N>& lhs)
        {
            for (size_t r = 0; r < lhs.row; ++r)
            {
                for (size_t c = 0; c < lhs.col; ++c)
                {
                    lhs[r][c] = static_cast<T>(r == c ? 1 : 0);
                }
            }
        }
        template <typename T, int M, int N>
        Matrix<T, N, M> Transpose(const Matrix<T, M, N>& lhs)
		{
            Matrix<T, N, M> ret;
            for (size_t r = 0; r < lhs.row; ++r)
            {
                for (size_t c = 0; c < lhs.col; ++c)
                {
                    ret[c][r] = lhs[r][c];
                }
            }
            return ret;
		}

        template <typename T, int N>
        T Dot(const Vector<T, N>& lhs, const Vector<T, N>& rhs)
        {
            T ret{0};
            for (auto i = 0; i < N; ++i) ret += lhs[i] * rhs[i];
            return ret;
        }

        template <typename T>
        Vector<T, 3> Cross(const Vector<T, 3>& lhs, const Vector<T, 3>& rhs)
        {
            return Vector<T, 3>(lhs.y() * rhs.z() - lhs.z() * rhs.y(),
                                lhs.z() * rhs.x() - lhs.x() * rhs.z(),
                                lhs.x() * rhs.y() - lhs.y() * rhs.x());
        }

        template <typename T>
        T Normalize(const T& rhs)
        {
            auto dot = Dot(rhs, rhs);
            CHECK_ASSERT(IsFloatEqual(dot, 0) == false);
            return rhs * InvSqrt(dot);
        }

        template <typename T, int N>
        Vector<T, N> TransformPoint(const Vector<T, N>& lhs,
                                    const Matrix<T, N, N>& rhs)
        {
            // the last element of position will be 1
            CHECK_ASSERT(IsFloatEqual(lhs[N - 1], 1));

            Vector<T, N> ret;
            for (size_t i = 0; i < lhs.size; ++i)
            {
                for (size_t j = 0; j < rhs.row; ++j)
                {
                    ret[i] += lhs[i] * rhs[i][j];
                }
            }
            ret *= 1.0f / ret[N - 1];
            return ret;
        }
        template <typename T, int N>
        Vector<T, N> TransformVector(const Vector<T, N>& lhs,
                                     const Matrix<T, N, N>& rhs)
        {
            // the last element of vector will be 0
            CHECK_ASSERT(IsFloatEqual(lhs[N - 1], 0));

            Vector<T, N> ret;
            for (size_t i = 0; i < lhs.size; ++i)
            {
                for (size_t j = 0; j < rhs.row; ++j)
                {
                    ret[i] += lhs[i] * rhs[i][j];
                }
            }
            return ret;
        }
        template <typename T, int N>
        Matrix<T, N, N> OuterProduct(Vector<T, N> const& lhs,
                                     Vector<T, N> const& rhs)
        {
            NOTIMPL_ASSERT();
        }

        template <typename T, int M, int S, int N>
        Matrix<T, M, N> Multiply(const Matrix<T, S, N>& lhs,
                                 const Matrix<T, M, S>& rhs)
        {
            // CHECK_ASSERT(lhs.row == rhs.col);
            Matrix<T, M, N> ret;

            for (size_t row = 0; row < lhs.row; ++row)
            {
                for (size_t col = 0; col < rhs.col; ++col)
                {
                    ret[row][col] = 0;
                    for (size_t i = 0; i < S; ++i)
                    {
                        ret[row][col] += lhs[row][i] * rhs[i][col];
                    }
                }
            }
            return ret;
        }

        template <typename T>
        Matrix<T, 4, 4> PerspectiveFovLH(const T fovy, const T aspect,
                                         const T zn, const T zf)
        {
            float y_scale = Cot(fovy / 2);
            float x_scale = y_scale / aspect;
            float m33 = zf / (zf - zn);

            return Matrix<T, 4, 4>(
                x_scale,    0, 0,         0,
                0,    y_scale, 0,         0,
                0,          0, m33,       1, 
                0,          0, -zn * m33, 0);
        }

    }  // namespace Math
}  // namespace vEngine

#endif /* _MATH_HPP */
