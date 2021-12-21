#ifndef _PREDECLEAR_HPP
#define _PREDECLEAR_HPP

namespace vEngine
{
    namespace Core
    {
        class Window;

        template <typename T, int N>
        class Vector;

        typedef Vector<int, 1> int1;
        typedef Vector<int, 2> int2;
        typedef Vector<int, 3> int3;
        typedef Vector<int, 4> int4;

        typedef Vector<float, 1> float1;
        typedef Vector<float, 2> float2;
        typedef Vector<float, 3> float3;
        typedef Vector<float, 4> float4;

        typedef Vector<double, 1> double1;
        typedef Vector<double, 2> double2;
        typedef Vector<double, 3> double3;
        typedef Vector<double, 4> double4;

        template <typename T, int M, int N>
        class Matrix;

        typedef Matrix<float, 4, 4> float4x4;

    }  // namespace Core
}  // namespace vEngine

#endif /* _PREDECLEAR_HPP */
