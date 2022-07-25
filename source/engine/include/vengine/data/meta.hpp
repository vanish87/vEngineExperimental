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
        struct DefaultGetter
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


// Sample implementation of a json-like data structure. It is only there for the example to compile and actually produce a testable output
namespace Json
{
    struct Value;

    struct ValueData
    {
            std::map<std::string, Value> subObject;
            std::string string;
            int number = 0;
            vEngine::Core::float4 numberf;
            vEngine::Core::Attribute<int> attri;
            vEngine::Core::Attribute<std::string> attri_tex;
            vEngine::Core::TexAttribute tex;
    };

    struct Value
    {
            ValueData data;

            Value& operator[](std::string name)
            {
                return data.subObject[std::move(name)];
            }

            const Value& operator[](std::string name) const
            {
                auto it = data.subObject.find(std::move(name));

                if (it != data.subObject.end())
                {
                    return it->second;
                }

                throw;
            }

            Value& operator=(std::string value)
            {
                data.string = value;
                return *this;
            }

            Value& operator=(int value)
            {
                data.number = value;
                return *this;
            }
            Value& operator=(vEngine::Core::float4 value)
            {
                data.numberf = value;
                return *this;
            }
            Value& operator=(vEngine::Core::Attribute<int> value)
            {
                data.attri.Set(value.Get());
                return *this;
            }
            Value& operator=(vEngine::Core::Attribute<std::string> value)
            {
                data.attri_tex.Set(value.Get());
                return *this;
            }
            Value& operator=(vEngine::Core::TexAttribute value)
            {
                data.tex.Set(value.Get());
                return *this;
            }
    };

    template <typename T>
    T& asAny(Value&);
    template <typename T>
    const T& asAny(const Value&);

}  // namespace Json
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

                // attri_ref_getter_func_ptr<T> refGetterPtr;
                // ref_setter_func_ptr_t refSetterPtr;
                // public:
                //     operator const T&() const
                //     {
                //         return this->Get(this->*member);
                //     }
        };

        template <typename Class, typename T>
        constexpr auto property(const char* name, Attribute<T> Class::*member)
        {
            // UNUSED_PARAMETER(getter);
            return Property<Class, Attribute<T>, T>{name, member};
        };
        template <typename Class, typename T>
        constexpr auto property(const char* name, T Class::*member)
        {
            // UNUSED_PARAMETER(getter);
            return Property<Class, T, T>{name, member};
        };
        class JsonFunction
        {
            public:
                template <typename T>
                static Json::Value toJson(const T& object)
                {
                    Json::Value data;
                    UNUSED_PARAMETER(object);

                    // We first get the number of properties
                    constexpr auto nbProperties = std::tuple_size<decltype(T::properties())>::value;

                    // We iterate on the index sequence of size `nbProperties`
                    for_sequence(std::make_index_sequence<nbProperties>{},
                                 [&](auto i)
                                 {
                                     // get the property
                                     constexpr auto property = std::get<i>(T::properties());
                                    //  property.Get(object);

                                     // set the value to the member
                                    //  data[property.name] = (object.*(property.member));
                                     // Or using streaming
                                     // stream << object.*(property.member);
                                 });

                    return data;
                }
                template <typename T>
                static T fromJson(const Json::Value& data)
                {
                    T object;
                    UNUSED_PARAMETER(data);

                    // We first get the number of properties
                    constexpr auto nbProperties = std::tuple_size<decltype(T::properties())>::value;

                    // We iterate on the index sequence of size `nbProperties`
                    for_sequence(std::make_index_sequence<nbProperties>{},
                                 [&](auto i)
                                 {
                                     // get the property
                                     constexpr auto property = std::get<i>(T::properties());

                                     // get the type of the property
                                     using Type = typename decltype(property)::value_type;

                                     // set the value to the member
                                     // you can also replace `asAny` by `fromJson` to recursively serialize
                                    //  object.*(property.member) = ::Json::asAny<Type>(data[property.name]);
                                     //  object.*(property.member) = JsonFunction::fromJson<Type>(data[property.name]);
                                     // Or using streaming
                                     // stream >> object.*(property.member);
                                });

                    return object;
                }
        };
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class Meta
        {
            public:
                /// \brief brief constructor description.
                Meta();
                virtual ~Meta();

                // void Serialize(ISerializable data)
                // {
                //     // data.setvalue<int>("x", x):
                // }
                // void Deserialize(ISerializable data)
                // {
                //     // this->x = data.getvalue<int>("x", x):
                // }

            public:
                /// \brief A brief function description.
                ///
                /// \param p1 Description for p1.
                /// \param p2 Description for p2.
                /// \return Description for return value.
                int GetVariable(int p1, float p2);
        };


        // static constexpr Property<class, type> _##var##_pro{&class::_##var, #var};

        // static constexpr property _##var##_pro(&class::_##var, #var);
        // static constexpr auto _##var##_pro(){return property(&class::_##var, #var);}



        class Dog
        {
                // template <typename Class, typename T>
                // friend struct Property;

                friend class JsonFunction;
                // friend struct Property;

                // std::string barkType;
                std::string color;
                int weight = 0;
                float num = 0.1f;

            public:
                vEngine::Core::float4x4 newWeight;

                PROPERTY(std::string, bark_type);

                public:
                    Attribute<int> my_attribute_;
                    Attribute<vEngine::Core::float4> my_float4_;
                    Attribute<std::string> my_string_;
                    // TexAttribute my_attribute_tex_;

                    bool operator==(const Dog& rhs) const
                    {
                        return std::tie(_bark_type, color, weight) == std::tie(rhs._bark_type, rhs.color, rhs.weight);
                }

                constexpr static auto properties()
                {
                    return std::make_tuple(
                        // property(&Dog::newWeight, "newWeight"),
                        // _barkType_pro,
                        // property("barkType", &Dog::_bark_type, &Dog::Get_bark_type)
                        property("barkType", &Dog::my_attribute_),
                        property("tex", &Dog::my_string_),
                        property("color", &Dog::color),
                        property("weight",&Dog::weight),
                        property("weightn32",&Dog::newWeight),
                        property("myforlaot4",&Dog::my_float4_),
                        property("flaot",&Dog::num)
                    );
                    // property(&Dog::my_attribute_, "MyAttribute", ));
                };
        };
    }  // namespace Data

}  // namespace vEngine

#endif /* _VENGINE_DATA_META_HPP */
