/// \file meta.hpp
/// \brief Head file for Meta
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_DATA_JSON_HPP
#define _VENGINE_DATA_JSON_HPP

#pragma once

#include <engine.hpp>
#include <external/json.hpp>

namespace vEngine
{
    namespace Core
    {
        template <typename T>
        nlohmann::json ToJson(const T& obj)
        {
            nlohmann::json value;
            constexpr auto nbProperties = std::tuple_size<decltype(T::properties())>::value;

            // We iterate on the index sequence of size `nbProperties`
            for_sequence(std::make_index_sequence<nbProperties>{},
                         [&](auto i)
                         {
                             // get the property
                             constexpr auto property = std::get<i>(T::properties());
                             value[property.name] = ToJson(obj.*(property.member));
                             //  ToJson(v, obj.*(property.member));
                             // Or using streaming
                             // stream << object.*(property.member);
                         });
            return value;
        }
        template <typename T>
        void ToJson(nlohmann::json& j, const T& obj)
        {
            j = ToJson(obj);
        }

        // template <>
        // nlohmann::json ToJson(const bool& obj)
        // {
        //     return nlohmann::json(obj);
        // }
        template <>
        nlohmann::json ToJson(const int& obj)
        {
            return nlohmann::json(obj);
        }
        template <>
        nlohmann::json ToJson(const float& obj)
        {
            return nlohmann::json(obj);
        }
        template <>
        nlohmann::json ToJson(const std::string& obj)
        {
            return nlohmann::json(obj);
        }
        // template <typename T, int N>
        // nlohmann::json ToJson(const std::array<T,N>& obj)
        // {
        //     static_assert(false, "Should used vengine data types for serializer")
        //     UNUSED_PARAMETER(obj);
        //     return nlohmann::json();
        // }
        template <typename T, int N>
        nlohmann::json ToJson(const Vector<T,N>& vector)
        {
            nlohmann::json value;
            auto id = 0;
            for(const auto& e : vector)
            {
                value[id++] = e;
            }
            return value;
        }
        template <typename T, int M, int N>
        nlohmann::json ToJson(const Matrix<T,M,N>& matrix)
        {
            nlohmann::json value;
            auto id = 0;
            for(const auto& row : matrix)
            {
                value[id++] = ToJson(row);
            }
            return value;
        }


        template <typename T>
        static void FromJson(const nlohmann::json& j, T& object)
        {
            // T object;

            // We first get the number of properties
            constexpr auto nbProperties = std::tuple_size<decltype(T::properties())>::value;

            // We iterate on the index sequence of size `nbProperties`
            for_sequence(std::make_index_sequence<nbProperties>{},
                         [&](auto i)
                         {
                             // get the property
                             constexpr auto property = std::get<i>(T::properties());

                             // get the type of the property
                            //  using Type = typename decltype(property)::member_type;

                             // set the value to the member
                             // you can also replace `asAny` by `fromJson` to recursively serialize
                             FromJson(j[property.name], object.*(property.member));
                            //  object.*(property.member) = j[property.name].template get<Type>();
                             //  object.*(property.member) = JsonFunction::fromJson<Type>(data[property.name]);
                             // Or using streaming
                             // stream >> object.*(property.member);
                         });

            // return object;
        }

        // template<>
        // void FromJson(const nlohmann::json& j, bool& obj)
        // {
        //     obj = j.get<bool>();
        // }
        template<>
        void FromJson(const nlohmann::json& j, int& obj)
        {
            obj = j.get<int>();
        }
        template<>
        void FromJson(const nlohmann::json& j, float& s)
        {
            s = j.get<float>();
        }
        template<>
        void FromJson(const nlohmann::json& j, std::string& s)
        {
            s = j.get<std::string>();
        }
        // template<>
        // void FromJson(const nlohmann::json& j, std::array<float,4>& arr)
        // {
        //     UNUSED_PARAMETER(j);
        //     UNUSED_PARAMETER(arr);
        // }
        template<typename T, int N>
        void FromJson(const nlohmann::json& j, Vector<T,N>& arr)
        {
            UNUSED_PARAMETER(j);
            UNUSED_PARAMETER(arr);
        }
        template <typename T, int M, int N>
        void FromJson(const nlohmann::json& j, Matrix<T, M, N>& arr)
        {
            UNUSED_PARAMETER(j);
            UNUSED_PARAMETER(arr);
        }

        template<typename T, int N>
        void FromJson(const nlohmann::json& j, std::array<T,N>& arr)
        {
            UNUSED_PARAMETER(j);
            UNUSED_PARAMETER(arr);
        }
        // template<>
        // template<typename T, int N>
        // vEngine::Core::Vector<T,N> FromJson(const nlohmann::json& j)
        // {
        //     vEngine::Core::Vector<T,N> v;
        //     return v;
        // }

    }  // namespace Core
}

#endif /* _VENGINE_DATA_JSON_HPP */