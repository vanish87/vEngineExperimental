#ifndef _INCLUDE_PREDECLEAR_HPP
#define _INCLUDE_PREDECLEAR_HPP

#include <cstdint>
#include <memory>

namespace vEngine
{
    typedef std::int8_t int8_t;
    typedef std::int16_t int16_t;
    typedef std::int32_t int32_t;
    typedef std::int64_t int64_t;

    typedef unsigned char byte;
    typedef std::uint8_t uint8_t;
    typedef std::uint16_t uint16_t;
    typedef std::uint32_t uint32_t;
    typedef std::uint64_t uint64_t;
    namespace Math
    {
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
    }  // namespace Math
    namespace Core
    {
        class Window;
        typedef std::shared_ptr<Window> WindowPtr;
        class Application;
    }  // namespace Core
    namespace Rendering
    {
        class RenderEngine;
    }
}  // namespace vEngine

#endif /* _INCLUDE_PREDECLEAR_HPP */
