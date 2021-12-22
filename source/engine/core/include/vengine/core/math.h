#ifndef _VENGINE_MATH_H
#define _VENGINE_MATH_H

#include <CORE_API.h>

#include <cmath>
#include <vengine/core/predeclear.hpp>

namespace vEngine
{
    /// \brief Math Functions
    namespace Math
    {
        /// \brief PI constant
        float const PI = 3.141592653f;

        /// \brief E constant
        float const E = 2.718281828f;

        /// \brief if a number(only float/double) is NAN(not a number)
        ///
        /// \tparam T should be float/double, int will be a compile error
        /// \param x
        /// \return true
        /// \return false
        template <typename T>
        bool IsNAN(T& x);

        /// \brief if a number is INF(infinity)
        ///
        /// \tparam T
        /// \param x
        /// \return true
        /// \return false
        template <typename T>
        bool IsINF(T& x);

        /// \brief return absolute of a number
        ///
        /// \param num
        /// \return float
        float Abs(float num);

        /// \brief Check if two floats are equal
        ///
        /// \param lhs
        /// \param rhs
        /// \return true
        /// \return false
        bool CORE_API IsFloatEqual(float& lhs, float& rhs);

        /// \brief Check if two const floats are equal
        ///
        /// \param lhs
        /// \param rhs
        /// \return true
        /// \return false
        bool CORE_API IsFloatEqual(const float& lhs, const float& rhs);

        /// \brief Check if two floats are less different than epsilon
        ///
        /// \param lhs
        /// \param rhs
        /// \param epsilon
        /// \return true
        /// \return false
        bool IsFloatEqual(float& lhs, float& rhs, float epsilon);

        template <typename T>
        T Min(T& lhs, T& rhs);
        template <typename T>
        T Max(T& lhs, T& rhs);

        float Sqrt(float x);
        float Sin(float x);
        float Cos(float x);
        float ArcCos(float x);
        float Tan(float x);
        float ArcTan(float x);
        float Cot(float x);
        float InvSqrt(float number);

        float Ln(float x);
        float Pow(float base, float exp);

        template <typename T>
        T Min(T& lhs, T& rhs);
        template <typename T>
        T Max(T& lhs, T& rhs);

        template <typename T, int M = 4, int N = 4>
        Matrix<T, M, N> Multiply(const Matrix<T, M, N>& lhs,
                                 const Matrix<T, M, N>& rhs);

    }  // namespace Math
}  // namespace vEngine

#include <vengine/core/math.hpp>
#endif /* _MATH_H */