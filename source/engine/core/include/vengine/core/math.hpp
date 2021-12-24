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
        template <typename T, int M, int N>
        Matrix<T, M, N> OuterProduct(const Vector<T, M>& lhs,
                                     const Vector<T, N>& rhs)
        {
            Matrix<T, M, N> ret;

            for (size_t n = 0; n < N; ++n)
            {
                for (size_t m = 0; m < M; ++m)
                {
                    ret[n][m] = lhs[m] * rhs[n];
                }
            }

            return ret;
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
        T Determinant(const Matrix<T, 4, 4>& matrix)
        {
            // from KlayGE
            T const _3142_3241(matrix[2][0] * matrix[3][1] -
                               matrix[2][1] * matrix[3][0]);
            T const _3143_3341(matrix[2][0] * matrix[3][2] -
                               matrix[2][2] * matrix[3][0]);
            T const _3144_3441(matrix[2][0] * matrix[3][3] -
                               matrix[2][3] * matrix[3][0]);
            T const _3243_3342(matrix[2][1] * matrix[3][2] -
                               matrix[2][2] * matrix[3][1]);
            T const _3244_3442(matrix[2][1] * matrix[3][3] -
                               matrix[2][3] * matrix[3][1]);
            T const _3344_3443(matrix[2][2] * matrix[3][3] -
                               matrix[2][3] * matrix[3][2]);

            return matrix[0][0] *
                       (matrix[1][1] * _3344_3443 - matrix[1][2] * _3244_3442 +
                        matrix[1][3] * _3243_3342) -
                   matrix[0][1] *
                       (matrix[1][0] * _3344_3443 - matrix[1][2] * _3144_3441 +
                        matrix[1][3] * _3143_3341) +
                   matrix[0][2] *
                       (matrix[1][0] * _3244_3442 - matrix[1][1] * _3144_3441 +
                        matrix[1][3] * _3142_3241) -
                   matrix[0][3] *
                       (matrix[1][0] * _3243_3342 - matrix[1][1] * _3143_3341 +
                        matrix[1][2] * _3142_3241);
        }
        template <typename T>
        Matrix<T, 4, 4> LookAtLH(const Vector<T, 3>& eye,
                                 const Vector<T, 3>& at, const Vector<T, 3>& up)
        {
            auto zaxis = Normalize(at - eye);
            auto xaxis = Normalize(Cross(up, zaxis));
            auto yaxis = Cross(zaxis, xaxis);

            return Matrix<T, 4, 4>(
                xaxis.x(), yaxis.x(), zaxis.x(), 0,
                xaxis.y(), yaxis.y(), zaxis.y(), 0,
                xaxis.z(), yaxis.z(), zaxis.z(), 0,
                -Dot(xaxis, eye), -Dot(yaxis, eye), -Dot(zaxis, eye), 1);
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

        template <typename T>
        void XRotation(Matrix<T, 4, 4>& matrix, const float theta)
        {
            Identity(lhs);
            lhs[1][1] = Math::Cos(theta);
            lhs[1][2] = Math::Sin(theta);
            lhs[2][1] = -Math::Sin(theta);
            lhs[2][2] = Math::Cos(theta);
        }

        template <typename T>
        void YRotation(Matrix<T, 4, 4>& lhs, const float theta)
        {
            Identity(lhs);
            lhs[0][0] = Math::Cos(theta);
            lhs[0][2] = -Math::Sin(theta);
            lhs[2][0] = Math::Sin(theta);
            lhs[2][2] = Math::Cos(theta);
        }

        template <typename T>
        void ZRotation(Matrix<T, 4, 4>& lhs, const float theta)
        {
            Identity(lhs);
            lhs[0][0] = Math::Cos(theta);
            lhs[0][1] = Math::Sin(theta);
            lhs[1][0] = -Math::Sin(theta);
            lhs[1][1] = Math::Cos(theta);
        }

        template <typename T>
        void RotationAxis(Matrix<T, 4, 4>& lhs, const Vector<T, 3>& axis,
                          const float theta)
        {
            Identity(lhs);
            axis = Normalize(axis);

            lhs[0][0] = (1.0f - Cos(theta)) * axis.x() * axis.x() + Cos(theta);
            lhs[1][0] = (1.0f - Cos(theta)) * axis.x() * axis.y() +
                        Sin(theta) * axis.z();
            lhs[2][0] = (1.0f - Cos(theta)) * axis.x() * axis.z() -
                        Sin(theta) * axis.y();
            lhs[0][1] = (1.0f - Cos(theta)) * axis.y() * axis.x() -
                        Sin(theta) * axis.z();
            lhs[1][1] = (1.0f - Cos(theta)) * axis.y() * axis.y() + Cos(theta);
            lhs[2][1] = (1.0f - Cos(theta)) * axis.y() * axis.z() +
                        Sin(theta) * axis.x();
            lhs[0][2] = (1.0f - Cos(theta)) * axis.z() * axis.x() +
                        Sin(theta) * axis.y();
            lhs[1][2] = (1.0f - Cos(theta)) * axis.z() * axis.y() -
                        Sin(theta) * axis.x();
            lhs[2][2] = (1.0f - Cos(theta)) * axis.z() * axis.z() + Cos(theta);
        }

        template <typename T>
        void Translate(Matrix<T, 4, 4>& lhs, const float x, const float y,
                       const float z)
        {
            Identity(lhs);
            // left hand coordinate system
            lhs[3][0] = x;
            lhs[3][1] = y;
            lhs[3][2] = z;
        }

        template <typename T>
        void Scale(Matrix<T, 4, 4>& lhs, const float scale)
        {
            Identity(lhs);

            lhs[0][0] = scale;
            lhs[1][1] = scale;
            lhs[2][2] = scale;
        }

    }  // namespace Math
}  // namespace vEngine

#endif /* _MATH_HPP */
