/// \file meta.hpp
/// \brief Head file for Meta
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_DATA_META_HPP
#define _VENGINE_DATA_META_HPP

#pragma once

#include <engine.hpp>

#include <map>
#include <vengine/core/vector.hpp>
#include <vengine/core/matrix.hpp>

namespace vEngine
{
    namespace Core
    {
        template <typename T>
        class Attribute
        {
            protected:
                T value_;

            public:
                Attribute() {}
                Attribute(const T& v) : value_{v} {}
                virtual const T& Get() const
                {
                    return this->value_;
                }
                virtual void Set(const T& value)
                {
                    this->value_ = value;
                }
                virtual Attribute<T>& operator=(const Attribute<T>& other) noexcept
                {
                    // 1.check self assignment
                    if (this != &other)
                    {
                        // 2.allocate new object before-> to assure memory
                        // before delete existing one
                        this->value_ = other.value_;
                    }
                    return *this;
                }
                constexpr static auto properties()
                {
                    return std::make_tuple(
                        property("attribute_value", &Attribute::value_)
                    );
                }
        };
        class TexAttribute : public Attribute<std::string>
        {

        };
        template<typename T>
        struct Getter
        {
            static const T& Get(const T& value)
            {
                return value;
            }
        };
        template <typename T>
        struct Setter
        {
                static void Set(T& value, const T& var)
                {
                    value = T(var);
                }
        };
    }
}

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        // sequence for
        template <typename T, T... S, typename F>
        constexpr void for_sequence(std::integer_sequence<T, S...>, F&& f)
        {
            using unpack_t = int[];
            (void)unpack_t{(static_cast<void>(f(std::integral_constant<T, S>{})), 0)..., 0};
        }
        // template <typename T>
        // using attri_ref_getter_func_ptr = const T& (Attribute<T>::*)() const;
        // template <typename Class, typename T>
        // using member_ptr_t = T Class::*;


        template <typename Class, typename Member, typename Value>
        struct Property
        {
                using class_type = Class;
                using member_type = Member;
                using value_type = Value;
                // using ref_getter_func_ptr_t = const member_type& (Class::*)() const;
                // using ref_setter_func_ptr_t = void (Class::*)(const member_type&);

                // reference getter/setter func pointer type
                // template <typename Class, typename T>
                using ref_getter_func_ptr = const member_type& (class_type::*)() const;
                using ref_setter_func_ptr = void (class_type::*)(const member_type&);

                constexpr Property(const char* aName, member_type class_type::*aMember)
                 : name{aName}, member{aMember}, getter_ptr{nullptr}, setter_ptr{nullptr}{}

                // using Type = T;

                const char* name;
                member_type class_type::*member;

                ref_getter_func_ptr getter_ptr;
                ref_setter_func_ptr setter_ptr;
        };

        template <typename Class, typename T>
        constexpr auto property(const char* name, Attribute<T> Class::*member)
        {
            return Property<Class, Attribute<T>, T>{name, member};
        };
        template <typename Class, typename T>
        constexpr auto property(const char* name, T Class::*member)
        {
            return Property<Class, T, T>{name, member};
        };

    }  // namespace Data

}  // namespace vEngine

#endif /* _VENGINE_DATA_META_HPP */
