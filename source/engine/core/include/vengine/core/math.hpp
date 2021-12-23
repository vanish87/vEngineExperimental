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
        bool IsNAN(T& x)
        {
            return std::isnan(x);
        }

        template <typename T>
        bool IsINF(T& x)
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
        T Dot(Vector<T, N> const& lhs, Vector<T, N> const& rhs)
        {
            T ret{0};
            for(auto i = 0; i < N; ++i) ret += lhs[i] * rhs[i];
            return ret;
        }

        template <typename T>
        Vector<T, 3> Cross(Vector<T, 3> const& lhs, Vector<T, 3> const& rhs)
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

        template <typename T, int I, int J, int K>
        Matrix<T, I, K> Multiply(const Matrix<T, I, J>& lhs,
                                 const Matrix<T, J, K>& rhs)
        {
            CHECK_ASSERT(lhs.col == rhs.row);
            Matrix<T, I, K> ret;

            for (auto row = 0; row < I; row++)
            {
                for (auto col = 0; col < K; col++)
                {
                    ret[row][col] = 0;
                    for (auto i = 0; i < J; i++)
                    {
                        ret[row][col] += lhs[row][i] * rhs[i][col];
                    }
                }
            }
            return ret;
        }
    }  // namespace Math
}  // namespace vEngine

#endif /* _MATH_HPP */
