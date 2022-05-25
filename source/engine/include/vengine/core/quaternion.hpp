/// \file quaternion.hpp
/// \brief Head file for Quaternion
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_QUATERNION_HPP
#define _VENGINE_CORE_QUATERNION_HPP

#pragma once

#include <engine.hpp>
#include <vengine/core/vector.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        class Radian
        {
        };
        class Degree
        {
        };

        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        template <typename T = float>
        class Quaternion
        {
            private:
                typedef Vector<T, 4> DataType;
                DataType data_;

            public:
                // define types like std did
                typedef typename DataType::value_type value_type;

                typedef value_type* pointer;
                typedef const value_type* const_pointer;

                typedef typename DataType::reference reference;
                typedef typename DataType::const_reference const_reference;

                typedef typename DataType::iterator iterator;
                typedef typename DataType::const_iterator const_iterator;

                typedef typename DataType::size_type size_type;
                typedef typename DataType::difference_type difference_type;

            public:
                iterator begin() noexcept
                {
                    return this->data_.begin();
                }
                const iterator begin() const noexcept
                {
                    return this->data_.begin();
                }

                iterator end() noexcept
                {
                    return this->data_.end();
                }
                const iterator end() const noexcept
                {
                    return this->data_.end();
                }

            public:
                pointer data() noexcept
                {
                    return &(this->data_[0]);
                }
                constexpr const_pointer data() const noexcept
                {
                    return &(this->data_[0]);
                }

                reference operator[](size_type index) noexcept
                {
                    CHECK_ASSERT(index < N);
                    return this->data_[index];
                }
                constexpr const_reference operator[](size_type index) const noexcept
                {
                    CHECK_ASSERT(index < N);
                    return this->data_[index];
                }

                void Norm();
                void Conjugate();
                void Inverse();
        };
    }  // namespace Core
}  // namespace vEngine
#endif /* _VENGINE_CORE_QUATERNION_HPP */
