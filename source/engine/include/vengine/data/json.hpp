/// \file json.hpp
/// \brief Head file for json
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_DATA_JSON_HPP
#define _VENGINE_DATA_JSON_HPP

#pragma once

#include <unordered_map>

#include <engine.hpp>
#include <external/json.hpp>

#include <vengine/core/game_object.hpp>

namespace vEngine
{
    namespace Core
    {
        template <typename T>
        struct is_basic_json_type
        {
                static constexpr auto value = std::is_arithmetic<T>::value || std::is_same<T, std::string>::value;
        };
        template <typename T, typename = std::enable_if_t<std::is_integral<T>::value, T>>
        std::string ToString(const T& obj)
        {
            return std::to_string(obj);
        }
        template <typename T, typename = std::enable_if_t<std::is_integral<T>::value, T>>
        const T FromString(const std::string& obj)
        {
            return std::stoi(obj);
        }
        template <typename T, typename = std::enable_if_t<std::is_same<T, std::string>::value, T>>
        std::string ToString(const std::string& obj)
        {
            return obj;
        }
        template <typename T, typename = std::enable_if_t<std::is_same<T, std::string>::value, T>>
        const std::string FromString(const std::string& obj)
        {
            return obj;
        }
        // public interface of ToJson
        template <typename T>
        static void ToJson(nlohmann::json& j, const T& obj)
        {
            j = ToJson(obj);
        }

        template <typename T, typename = std::enable_if_t<is_basic_json_type<T>::value, T>, typename = void>
        nlohmann::json ToJson(const T& obj)
        {
            return nlohmann::json(obj);
        }

        template <typename T, typename = std::enable_if_t<!is_basic_json_type<T>::value, T>>
        nlohmann::json ToJson(const T& obj)
        {
            nlohmann::json value;
            constexpr auto nbProperties = std::tuple_size<decltype(T::properties())>::value;
            //  using Type = typename decltype(property)::class_type;

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
        template <std::size_t I, class T, typename Src>
        auto GetByType(std::shared_ptr<Src> ptr)
        {
            using Type = std::tuple_element_t<I, T>;
            return std::dynamic_pointer_cast<Type>(ptr);
            // if (p != nullptr) return ToJson(*p.get());
            // else return nlohmann::json();
        }
        template <typename T>
        nlohmann::json ToJson(const std::shared_ptr<T>& ptr)
        {
            using list = std::tuple<TransformComponent, Transform, Mesh, MeshComponent>;
            constexpr auto nlist = std::tuple_size<list>::value;
            nlohmann::json value;
            for_sequence(std::make_index_sequence<nlist>{},
                         [&](auto i)
                         {
                             auto p =GetByType<i, list>(ptr);
                             //  auto p = Get<i, list, T>(ptr);
                             if (p!= nullptr)
                             {
                                 value = ToJson(*p.get());
                             }
                         });
            // TODO Use context map for shared ptr
            //save uuid and/or other necessary description with json value
            //so that FromJson can find/create objects from xx factory class
            if(!value.is_null()) return value;
            return ToJson(*ptr.get());
        }
        // template <typename T, typename = std::enable_if_t<std::is_base_of<GameObject, T>::value, T>, typename = void, typename = void>
        // nlohmann::json ToJson(const T& go)
        // {
        //     UNUSED_PARAMETER(go);
        //     nlohmann::json value;
        //     return value;
        //     // return ToJson(ptr);
        // }
        template <typename T>
        nlohmann::json ToJson(const std::vector<T>& vector)
        {
            nlohmann::json value;
            auto id = 0;
            for (const auto& e : vector)
            {
                value[id++] = ToJson(e);
            }
            return value;
        }
        template <typename T>
        nlohmann::json ToJson(const std::list<T>& list)
        {
            nlohmann::json value;
            auto id = 0;
            for (const auto& e : list)
            {
                value[id++] = ToJson(e);
            }
            return value;
        }
        template <typename T, typename S>
        nlohmann::json ToJson(const std::unordered_map<T, S>& umap)
        {
            nlohmann::json value;
            for (const auto& e : umap)
            {
                value[ToString<T>(e.first)] = ToJson(e.second);
            }
            return value;
        }
        template <typename T, int N>
        nlohmann::json ToJson(const std::array<T, N>& obj)
        {
            NOT_IMPL_ASSERT;
            static_assert(false, "Should used vengine data types for serializer") UNUSED_PARAMETER(obj);
            return nlohmann::json();
        }
        template <typename T, int N>
        nlohmann::json ToJson(const Vector<T, N>& vector)
        {
            nlohmann::json value;
            auto id = 0;
            for (const auto& e : vector)
            {
                value[id++] = ToJson(e);
            }
            return value;
        }
        template <typename T, int M, int N>
        nlohmann::json ToJson(const Matrix<T, M, N>& matrix)
        {
            nlohmann::json value;
            auto id = 0;
            for (const auto& row : matrix)
            {
                value[id++] = ToJson(row);
            }
            return value;
        }

        template <typename T, typename = std::enable_if_t<!is_basic_json_type<T>::value, T>>
        static void FromJson(const nlohmann::json& j, T& object)
        {
            constexpr auto nbProperties = std::tuple_size<decltype(T::properties())>::value;
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
        }

        template <typename T, typename = std::enable_if_t<is_basic_json_type<T>::value, T>, typename = void>
        void FromJson(const nlohmann::json& j, T& obj)
        {
            obj = j.get<T>();
        }
        template <typename T>
        void FromJson(const nlohmann::json& j, std::shared_ptr<T>& ptr)
        {
            auto v = new T();
            FromJson(j, *v);
            ptr.reset(v);
        }
        template <typename T>
        void FromJson(const nlohmann::json& j, std::vector<T>& vector)
        {
            for (auto it = j.begin(); it != j.end(); ++it)
            {
                T v;
                FromJson(*it, v);
                vector.push_back(v);
            }
        }
        template <typename T>
        void FromJson(const nlohmann::json& j, std::list<T>& list)
        {
            for (auto it = j.begin(); it != j.end(); ++it)
            {
                T v;
                FromJson(*it, v);
                list.push_back(v);
            }
        }
        template <typename T, typename S>
        void FromJson(const nlohmann::json& j, std::unordered_map<T, S>& map)
        {
            for (auto it = j.begin(); it != j.end(); ++it)
            {
                // TODO ToJson should cast key to string in order to recover it here
                auto k = FromString<T>(it.key());
                FromJson(it.value(), map[k]);
            }
        }
        // template<>
        // void FromJson(const nlohmann::json& j, std::array<float,4>& arr)
        // {
        //     UNUSED_PARAMETER(j);
        //     UNUSED_PARAMETER(arr);
        // }
        template <typename T, int N>
        void FromJson(const nlohmann::json& j, Vector<T, N>& vector)
        {
            auto idx = 0;
            for (auto it = j.begin(); it != j.end(); ++it)
            {
                FromJson(*it, vector[idx++]);
            }
        }
        template <typename T, int M, int N>
        void FromJson(const nlohmann::json& j, Matrix<T, M, N>& matrix)
        {
            auto idx = 0;
            for (auto it = j.begin(); it != j.end(); ++it)
            {
                Vector<T, N> r;
                FromJson(*it, r);
                matrix[idx++] = r;
            }
        }

        template <typename T, int N>
        void FromJson(const nlohmann::json& j, std::array<T, N>& arr)
        {
            NOT_IMPL_ASSERT;
            UNUSED_PARAMETER(j);
            UNUSED_PARAMETER(arr);
        }
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_DATA_JSON_HPP */
