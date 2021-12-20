#ifndef _TEMPLATE_HELPER_HPP
#define _TEMPLATE_HELPER_HPP

#pragma once

namespace vEngine
{
    namespace Core
    {
        template <typename T, int N>
        struct vector_t
        {
                template <typename U>
                static void do_copy(T v[N], const U rhs[N]) noexcept
                {
                    v[0] = static_cast<T>(rhs[0]);
                    vector_t<T, N - 1>::do_copy(v + 1, rhs + 1);
                }

                /// \brief Assign rhs to v recursively
				/// 
                ///	Only same type can do assignment
				/// detail
                ///
                /// \param v
                /// \param rhs
                static void do_assign(T v[N], const T rhs[N]) noexcept
                {
                    v[0] = rhs[0];
                    vector_t<T, N - 1>::do_assign(v + 1, rhs + 1);
                }

                static void do_assign(T v[N], const T& rhs) noexcept
                {
                    v[0] = rhs;
                    vector_t<T, N - 1>::do_assign(v + 1, rhs);
                }

                static void do_add(T v[N], const T lhs[N], const T rhs[N]) noexcept
                {
                    v[0] = lhs[0] + rhs[0];
                    vector_t<T, N - 1>::do_add(v + 1, lhs + 1, rhs + 1);
                }
        };

        template <typename T>
        struct vector_t<T, 1>
        {
                template <typename U>
                static void do_copy(T v[1], const U rhs[1]) noexcept
                {
                    v[0] = static_cast<T>(rhs[0]);
                }

                /// \brief base case of template recursive
                ///
                /// \param v
                /// \param rhs
                static void do_assign(T v[1], const T rhs[1]) noexcept
                {
                    v[0] = rhs[0];
                }
                static void do_assign(T v[1], const T& rhs) noexcept
                {
                    v[0] = rhs;
                }
                static void do_add(T v[1], const T lhs[1], const T rhs[1]) noexcept
                {
                    v[0] = lhs[0] + rhs[0];
                }
        };

    }  // namespace Core
}  // namespace vEngine

#endif /* _TEMPLATE_HELPER_HPP */
