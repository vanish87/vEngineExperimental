#ifndef _MATH_HPP
#define _MATH_HPP

#pragma once

namespace vEngine
{
    namespace Math
    {
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
    }  // namespace Math
}  // namespace vEngine

#endif /* _MATH_HPP */
