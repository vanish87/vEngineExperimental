#ifndef _MATH_HPP
#define _MATH_HPP

#pragma once


namespace vEngine
{
    /// \brief Math Functions
    ///
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

        template <typename T, int M, int N>
        Matrix<T, M, N> Multiply(const Matrix<T, M, N>& lhs,
                                 const Matrix<T, M, N>& rhs)
        {
            // CHECK_ASSERT(lhs.row() == rhs.col());
            Matrix<T, M, N> ret;
            std::size_t dim = M;

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
