
#include <vengine/data/class_foo.hpp>
#include <vengine/core/game_object_factory.hpp>

#define FROM_JSON_BY_DESC(desc, type_name, template_name)           \
if (desc.type == typeid(type_name).name())                          \
{                                                                   \
    auto go = GameObjectFactory::Create<type_name>();               \
    auto json = LoadJson(GameObjectToPath(desc));                   \
    FromJson(json, *go.get());                                      \
    return std::dynamic_pointer_cast<template_name>(go);            \
}

namespace vEngine
{
    namespace Core
    {
        template <typename T, typename = std::enable_if_t<is_basic_json_type<T>::value, T>, typename = void>
        void FromJson(const json& j, T& obj)
        {
            obj = j.get<T>();
        }

        template <typename T, typename = std::enable_if_t<!is_basic_json_type<T>::value, T>>
        void FromJson(const json& j, T& object)
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

        template <>
        void FromJson(const json& j, UUID& uuid)
        {
            auto id = j.get<uint64_t>();
            uuid.Set(id);
        }
        template <>
        void FromJson(const json& j, std::filesystem::path& path)
        {
            auto data = j.get<std::string>();
            path = data;
        }
        // template <typename T, typename = std::enable_if_t<std::is_same<T, GameObjectType>::value, T>, typename = void>
        template <>
        void FromJson(const json& j, GameObjectType& go_type)
        {
            NOT_IMPL_ASSERT;
            UNUSED_PARAMETER(j);
            UNUSED_PARAMETER(go_type);
            // return json(ToString<GameObjectType>(go_type));
        }
        template <>
        void FromJson(const json& j, Rendering::ShaderType& shader_type)
        {
            NOT_IMPL_ASSERT;
            UNUSED_PARAMETER(j);
            UNUSED_PARAMETER(shader_type);
            // return json(ToString<GameObjectType>(go_type));
        }

        template <typename T>
        void FromJson(const json& j, std::weak_ptr<T>& ptr)
        {
            // UNUSED_PARAMETER(j);
            // UNUSED_PARAMETER(ptr);

            auto shared = std::shared_ptr<T>();
            FromJson(j, shared);
            ptr = shared;
        }
        template <typename T>
        std::shared_ptr<T> CreateAndLoadByDesc(const GameObjectDescription& desc)
        {
            // if (type == "class vEngine::Core::CameraComponent") return Create<CameraComponent>();
            // if (type == "class vEngine::Core::TransformComponent") return Create<TransformComponent>();
            // if (type == "class vEngine::Core::Scene") return Create<Scene>();
            // if (type == "class vEngine::Core::GameNode") return Create<GameNode>();

            // auto type = desc.type;


            FROM_JSON_BY_DESC(desc, ClassFoo, T);
            FROM_JSON_BY_DESC(desc, ClassBar, T);

            // if (type == "class vEngine::Core::ClassFoo") 
            // {
            //     auto go = GameObjectFactory::Create<ClassFoo>();
            //     auto json = LoadJson(GameObjectToPath(desc));
            //     FromJson(json, *go.get());
            //     return std::dynamic_pointer_cast<T>(go);
            // }
            // if (type == "class vEngine::Core::ClassBar") 
            // {
            //     auto go = GameObjectFactory::Create<ClassBar>();
            //     auto json = LoadJson(GameObjectToPath(desc));
            //     FromJson(json, *go.get());
            //     return std::dynamic_pointer_cast<T>(go);
            // }
            // if (type == "class vEngine::Core::ClassBar") return Create<ClassBar>();
            return nullptr;
        }
        template <typename T>
        void FromJson(const json& j, std::shared_ptr<T>& ptr)
        {
            GameObjectDescription desc;
            FromJson(j["description"], desc);

            // PRINT("Deserialize " << desc.uuid.AsUint() << " " << desc.type);

            PRINT("From json load " << typeid(T).name());

            // 1. find by uuid
            ptr = GameObjectFactory::Find<T>(desc);
            if(ptr != nullptr) return;

            ptr = CreateAndLoadByDesc<T>(desc);
            CHECK_ASSERT_NOT_NULL(ptr);

            PRINT("Load " << ptr->description_.uuid.AsUint() << " " << desc.type);
        }
        template <typename T>
        void FromJson(const json& j, std::vector<T>& vector)
        {
            vector.clear();
            for (const auto& it : j)
            {
                T v;
                FromJson(it, v);
                vector.push_back(v);
            }
        }
        template <typename T>
        void FromJson(const json& j, std::list<T>& list)
        {
            list.clear();
            for (const auto& it : j)
            {
                T v;
                FromJson(it, v);
                list.push_back(v);
            }
        }
        template <typename T, typename S>
        void FromJson(const json& j, std::unordered_map<T, S>& map)
        {
            for (const auto& it : j)
            {
                // TODO ToJson should cast key to string in order to recover it here
                auto k = FromString<T>(it.key());
                FromJson(it.value(), map[k]);
            }
        }
        // template<>
        // void FromJson(const json& j, std::array<float,4>& arr)
        // {
        //     UNUSED_PARAMETER(j);
        //     UNUSED_PARAMETER(arr);
        // }
        template <typename T, int N>
        void FromJson(const json& j, Vector<T, N>& vector)
        {
            auto idx = 0;
            for (const auto& it : j)
            {
                FromJson(it, vector[idx++]);
            }
        }
        template <typename T, int M, int N>
        void FromJson(const json& j, Matrix<T, M, N>& matrix)
        {
            auto idx = 0;
            for (const auto& it : j)
            {
                FromJson(it, matrix[idx++]);
            }
        }

        template <typename T, int N>
        void FromJson(const json& j, std::array<T, N>& arr)
        {
            NOT_IMPL_ASSERT;
            UNUSED_PARAMETER(j);
            UNUSED_PARAMETER(arr);
        }
    }  // namespace Core
}  // namespace vEngine