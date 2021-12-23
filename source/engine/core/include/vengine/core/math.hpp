#ifndef _MATH_HPP
#define _MATH_HPP

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
