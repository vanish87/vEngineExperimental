#ifndef _VENGINE_MATH_H
#define _VENGINE_MATH_H

#include <CORE_API.h>

#include <cmath>
#include <vengine/core/predeclear.hpp>

namespace vEngine
{
    /// \brief Math Functions \n
    /// Brief contine
    ///
    /// This implementation of Math/Engine libraries basically follows
    /// conventions of DirectX/HLSL/Windows.
    ///
    /// Row major system
    /// ========================
    /// - Vector is row major [x,y,z,w]
    /// - Matrix is colum major \n
    /// \code
    /// [e0, e4, e8, e12]
    /// [e1, e5, e9, e13]
    /// [e2, e6, e10,e14]
    /// [e3, e7, e11,e15]
    /// \endcode
    ///
    /// Left-hand system
    /// ========================
    /// - Z-Axis positive direction points into screen
    /// - Direction of cross product of two vectors follows
    /// left hand rule(clock-wise)
    ///
    /// Left-multiply system
    /// ========================
    /// - Vector left multiply Matrix \n
    /// \code
    /// v[x,y,z,w]*[m00,m01,m02,m03]
    ///            [m10,m11,m12,m13]
    ///            [m20,m21,m22,m23]
    ///            [m30,m31,m32,m33]
    /// \endcode
    ///
    /// Matrix/Projection conversion
    /// ========================
    /// - Z value range [0,1]
    /// - Z value direction [near, far]
    ///
    /// Detailed Doc of Math Heading 1
    /// ========================
    /// Something after heading
    /// with function reference \ref Abs and \ref IsNAN
    namespace Math
    {
        /// \brief PI constant
        float const PI = 3.141592653f;

        /// \brief E constant
        float const E = 2.718281828f;

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
        bool CORE_API IsFloatEqual(float& lhs, float& rhs, const float epsilon);

        /// \brief Check if two floats are less different than epsilon
        ///
        /// \param lhs
        /// \param rhs
        /// \param epsilon
        /// \return true
        /// \return false
        bool CORE_API IsFloatEqual(const float& lhs, const float& rhs,
                                   const float epsilon);

        /// \brief return absolute of a number
        ///
        /// \param num
        /// \return float
        float CORE_API Abs(float num);

        float CORE_API Sqrt(float x);
        float CORE_API Sin(float x);
        float CORE_API Cos(float x);
        float CORE_API ArcCos(float x);
        float CORE_API Tan(float x);
        float CORE_API ArcTan(float x);
        float CORE_API Cot(float x);
        float CORE_API InvSqrt(float number);

        float CORE_API Ln(float x);
        float CORE_API Pow(float base, float exp);

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

        template <typename T>
        T Min(T& lhs, T& rhs);
        template <typename T>
        T Max(T& lhs, T& rhs);

        template <typename T, int N = 4>
        T Dot(Vector<T, N> const& lhs, Vector<T, N> const& rhs);

        template <typename T, int N = 4>
        Vector<T, N> Cross(Vector<T, N> const& lhs, Vector<T, N> const& rhs);

        template <typename T>
        T Normalize(T const& rhs);

        template <typename T, int N = 4>
        Vector<T, N> TransformPoint(const Vector<T, N>& lhs,
                                    const Matrix<T, N, N>& rhs);

        template <typename T, int N = 4>
        Vector<T, N> TransformVector(const Vector<T, N>& lhs,
                                     const Matrix<T, N, N>& rhs);

        template <typename T, int N = 4>
        Vector<T, N> Transform(const Vector<T, N>& lhs,
                               const Matrix<T, N, N>& rhs);

        template <typename T, int N = 4>
        Matrix<T, N, N> OuterProduct(Vector<T, N> const& lhs,
                                     Vector<T, N> const& rhs);

        template <typename T, int I = 4, int J = 4, int K = 4>
        Matrix<T, I, K> Multiply(const Matrix<T, I, J>& lhs,
                                 const Matrix<T, J, K>& rhs);

    }  // namespace Math
}  // namespace vEngine

// include template definitions after declearations above
// for separate declearation/definition of template functions
#include <vengine/core/math.hpp>
#endif /* _MATH_H */