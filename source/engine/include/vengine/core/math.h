#ifndef _VENGINE_CORE_MATH_H
#define _VENGINE_CORE_MATH_H

#pragma once
#include <VENGINE_API.h>

#include <engine.hpp>

namespace vEngine
{
    /// \brief Math Functions \n
    /// Brief contine
    ///
    /// This implementation of Math/Engine libraries basically follows
    /// conventions of DirectX/HLSL/Windows.
    ///
    /// System data pack
    /// ========================
    /// - Vector is row major [x,y,z,w]
    /// - Matrix is colum major(as default hlsl pack) \n
    /// https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-appendix-pre-pragma-pack-matrix
    /// \code
    /// [e0,  e4,  e8,  e12]
    /// [e1,  e5,  e8,  e13]
    /// [e2,  e6,  e10, e15]
    /// [e3,  e7,  e11, e15]
    /// \endcode
    /// - Matrix<T, M, N> will define a N x M matrix with N elements in each
    /// row, and M rows. \n So the row variable will be M, the col variable will
    /// be N
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
    /// v[x,y,z,w]*[m00,m10,m20,m30]
    ///            [m01,m11,m21,m31]
    ///            [m02,m12,m22,m22]
    ///            [m03,m13,m23,m33]
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

        //=================================================
        // float related functions

        /// \brief Check if two const floats are equal
        ///
        /// \param lhs
        /// \param rhs
        /// \return true
        /// \return false
        bool VENGINE_API IsFloatEqual(const float& lhs, const float& rhs);

        /// \brief Check if two floats are less different than epsilon
        ///
        /// \param lhs
        /// \param rhs
        /// \param epsilon
        /// \return true
        /// \return false
        bool VENGINE_API IsFloatEqual(const float& lhs, const float& rhs, const float epsilon);

        /// \brief return absolute of a number
        ///
        /// \param num
        /// \return float
        float VENGINE_API Abs(float num);

        float VENGINE_API Sqrt(float x);
        float VENGINE_API Sin(float x);
        float VENGINE_API Cos(float x);
        float VENGINE_API ArcCos(float x);
        float VENGINE_API Tan(float x);
        float VENGINE_API ArcTan(float x);
        float VENGINE_API Cot(float x);
        float VENGINE_API InvSqrt(float number);
        float VENGINE_API Ln(float x);
        float VENGINE_API Pow(float base, float exp);

        /// \brief if a number(only float/double) is NAN(not a number)
        ///
        /// \tparam T should be float/double, int will be a compile error
        /// \param x
        /// \return true
        /// \return false
        template <typename T>
        bool IsNAN(const T& x);

        /// \brief if a number is INF(infinity)
        ///
        /// \tparam T
        /// \param x
        /// \return true
        /// \return false
        template <typename T>
        bool IsINF(const T& x);

        template <typename T>
        T Min(const T& lhs, const T& rhs);
        template <typename T>
        T Max(const T& lhs, const T& rhs);

        template <typename T>
        T Clamp(const T& value, const T& min, const T& max);

        //=================================================
        // Vector/Matrix related functions

        template <typename T, int N = 4>
        void Identity(Matrix<T, N, N>& lhs);

        template <typename T, int M, int N>
        Matrix<T, N, M> Transpose(const Matrix<T, M, N>& lhs);

        template <typename T, int N = 4>
        T Dot(const Vector<T, N>& lhs, const Vector<T, N>& rhs);

        template <typename T>
        Vector<T, 3> Cross(const Vector<T, 3>& lhs, const Vector<T, 3>& rhs);

        template <typename T>
        T Normalize(const T& rhs);

        template <typename T, int N = 4>
        Vector<T, N> TransformPoint(const Vector<T, N>& lhs, const Matrix<T, N, N>& rhs);

        template <typename T, int N = 4>
        Vector<T, N> TransformVector(const Vector<T, N>& lhs, const Matrix<T, N, N>& rhs);

        template <typename T, int M = 4, int N = 4>
        Matrix<T, M, N> OuterProduct(const Vector<T, M>& lhs, const Vector<T, N>& rhs);

        // template <typename T, int M = 4, int N = 4>
        // Vector<T, M> Multiply(const Vector<T, M>& lhs,
        //                       const Matrix<T, M, N>& rhs);

        template <typename T, int M = 4, int S = 4, int N = 4>
        Matrix<T, M, N> Multiply(const Matrix<T, M, S>& lhs, const Matrix<T, S, N>& rhs);

        template <typename T>
        T Determinant(const Matrix<T, 4, 4>& matrix);

        template <typename T>
        Matrix<T, 4, 4> Inverse(const Matrix<T, 4, 4>& matrix);

        //=================================================
        // View/Projection related functions

        template <typename T>
        Matrix<T, 4, 4> LookAtLH(const Vector<T, 3>& eye, const Vector<T, 3>& at, const Vector<T, 3>& up);

        template <typename T>
        Matrix<T, 4, 4> PerspectiveFovLH(const T fovy, const T aspect, const T zn, const T zf);

        template <typename T>
        void XRotation(Matrix<T, 4, 4>& matrix, const float theta);

        template <typename T>
        void YRotation(Matrix<T, 4, 4>& lhs, const float theta);

        template <typename T>
        void ZRotation(Matrix<T, 4, 4>& lhs, const float theta);

        template <typename T>
        void RotationAxis(Matrix<T, 4, 4>& lhs, const Vector<T, 3>& axis, const float theta);

        template <typename T>
        void Translate(Matrix<T, 4, 4>& lhs, const Vector<T, 3> xyz);
        template <typename T>
        void Translate(Matrix<T, 4, 4>& lhs, const float x, const float y, const float z);

        template <typename T>
        void Scale(Matrix<T, 4, 4>& lhs, const float scale);
        template <typename T>
        void Scale(Matrix<T, 4, 4>& lhs, const Vector<T, 3> scale);

    }  // namespace Math
}  // namespace vEngine

// include template definitions after declearations above
// for separate declearation/definition of template functions
#include <vengine/core/math.hpp>
#endif /* _VENGINE_CORE_MATH_H */
