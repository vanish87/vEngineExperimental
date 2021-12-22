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
            std::size_t dim = J;

            for (int row = 0; row < dim; row++)
                for (int col = 0; col < dim; col++)
                {
                    ret[row][col] = 0;
                    for (int i = 0; i < dim; i++)
                        ret[row][col] += lhs[row][i] * rhs[i][col];
                }
            return ret;
		}
    }  // namespace Math
}  // namespace vEngine

#endif /* _MATH_HPP */
