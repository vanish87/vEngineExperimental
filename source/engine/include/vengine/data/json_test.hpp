#ifndef _VENGINE_DATA_JSON_TEST_HPP
#define _VENGINE_DATA_JSON_TEST_HPP

#pragma once

#include <engine.hpp>
#include <vengine/data/json.hpp>

namespace vEngine
{
    namespace Core
    {
        template <typename T, typename = std::enable_if_t<is_basic_json_type<T>::value, T>, typename = void>
        json ToJsonTest(const T& obj)
        {
            return json(obj);
        }

        template <typename T, typename = std::enable_if_t<!is_basic_json_type<T>::value, T>>
        json ToJsonTest(const T& obj)
        {
            json value;
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

        template <typename T>
        json ToJsonTest(const std::weak_ptr<T>& ptr)
        {
            auto shared = ptr.lock();
            auto go = std::dynamic_pointer_cast<GameObject>(shared);
            if (go != nullptr)
            {
                return ToJson(*go.get());
            }
            return json();
        }

        template <typename T>
        json ToJsonTest(const std::shared_ptr<T>& ptr)
        {
            auto content_saved = false;

            using type_list = std::tuple<ClassFoo, ClassBar>;
            constexpr auto nlist = std::tuple_size<type_list>::value;
            for_sequence(std::make_index_sequence<nlist>{},
                         [&](auto i)
                         {
                             auto p = CastByType<i, type_list>(ptr);
                             if (!content_saved && p != nullptr)
                             {
                                 content_saved = true;

                                 auto value = ToJsonTest(*p.get());
                                 auto path = GameObjectToPath(p->description_);
                                 SaveJson(value, path);
                             }
                         });

            // if (!value.is_null()) return value;
            // NOT_IMPL_ASSERT;

            // only return GameObject info here
            auto go = std::dynamic_pointer_cast<GameObject>(ptr);
            auto value = ToJson(*go.get());
            return value;
        }

        template <typename T, typename = std::enable_if_t<is_basic_json_type<T>::value, T>, typename = void>
        void FromJsonTest(const json& j, T& obj)
        {
            obj = j.get<T>();
        }

        template <typename T, typename = std::enable_if_t<!is_basic_json_type<T>::value, T>>
        void FromJsonTest(const json& j, T& object)
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
                             FromJsonTest(j[property.name], object.*(property.member));
                             //  object.*(property.member) = j[property.name].template get<Type>();
                             //  object.*(property.member) = JsonFunction::fromJson<Type>(data[property.name]);
                             // Or using streaming
                             // stream >> object.*(property.member);
                         });
        }
        template <typename T>
        void FromJsonTest(const json& j, std::weak_ptr<T>& ptr)
        {
            UNUSED_PARAMETER(j);
            UNUSED_PARAMETER(ptr);
        }
        template <typename T>
        void FromJsonTest(const json& j, std::shared_ptr<T>& ptr)
        {
            GameObjectDescription desc;
            // FromJson(j["data"], *v);

            FromJson(j["description"], desc);

            // PRINT("Deserialize " << desc.uuid.AsUint() << " " << desc.type);

            // 1. find by uuid
            ptr = GameObjectFactory::Find<T>(desc);
            if(ptr != nullptr) return;

            ptr = GameObjectFactory::CreateByDesc<T>(desc);
            auto json = ParseJson(GameObjectToPath(desc));

            auto content_loaded = false;
            using type_list = std::tuple<ClassBar, ClassFoo>;
            constexpr auto nlist = std::tuple_size<type_list>::value;
            for_sequence(std::make_index_sequence<nlist>{},
                         [&](auto i)
                         {
                             auto p = CastByType<i, type_list>(ptr);
                             if (!content_loaded && p != nullptr)
                             {
                                 content_loaded = true;
                                 FromJsonTest(json, *p.get());
                             }
                         });

            PRINT("Load " << ptr->description_.uuid.AsUint() << " " << desc.type);
        }
        template <typename T, int N>
        void FromJsonTest(const json& j, Vector<T, N>& vector)
        {
            for (auto& i : vector)
            {
                FromJsonTest(j, i);
            }
        }
        template <typename T>
        void FromJsonTest(const json& j, std::vector<T>& vector)
        {
            for (auto it = j.begin(); it != j.end(); ++it)
            {
                T v;
                FromJsonTest(*it, v);
                vector.push_back(v);
            }
        }
        template <>
        void FromJsonTest(const json& j, UUID& uuid)
        {
            auto id = j.get<uint64_t>();
            uuid.Set(id);
        }
        template <>
        void FromJsonTest(const json& j, std::filesystem::path& path)
        {
            path = j.get<std::string>();
        }

    }  // namespace Core

}  // namespace vEngine

#endif /* _VENGINE_DATA_JSON_TEST_HPP */
