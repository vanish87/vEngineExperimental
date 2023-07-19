
#include <vengine/core/game_object_factory.hpp>
    
namespace vEngine
{
    namespace Core
    {
        template <typename T, typename, typename>
        void FromJson(const json& j, T& obj)
        {
            obj = j.get<T>();
        }

        template <typename T>
        void FromJson(const json& j, std::weak_ptr<T>& ptr)
        {
            if(j.is_null())
            {
                PRINT("json is null, it should be a nullptr");
                return;
            }
            GameObjectDescriptor desc;
            FromJson(j["meta"], desc);

            auto go = ResourceManager::GetInstance().FindOrCreate(desc);
            ptr = std::dynamic_pointer_cast<T>(go);
        }

        template <typename T>
        void FromJson(const json& j, std::shared_ptr<T>& ptr)
        {
            if(j.is_null())
            {
                PRINT("json is null, it should be a nullptr");
                return;
            }
            GameObjectDescriptor desc;
            FromJson(j["meta"], desc);

            // 1. find by uuid
            auto go = ResourceManager::GetInstance().FindOrCreate(desc);
            ptr = std::dynamic_pointer_cast<T>(go);
            // if(ptr != nullptr) return;
            // CHECK_ASSERT(ptr == nullptr);

            // ptr = CreateAndLoadByDesc<T>(desc);
            CHECK_ASSERT_NOT_NULL(ptr);

            // PRINT("Load " << ptr->descriptor_.uuid.AsUint() << " " << ToString(desc.type));
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

        template <typename T>
        void FromJson(const json& j, std::unordered_set<T>& set)
        {
            for (auto it = j.begin(); it != j.end(); ++it)
            {
                // TODO ToJson should cast key to string in order to recover it here
                T value;
                FromJson(it.value(), value);
                set.insert(value);
            }
        }
        template <typename T, typename S>
        void FromJson(const json& j, std::unordered_map<T, S>& map)
        {
            for (auto it = j.begin(); it != j.end(); ++it)
            {
                // TODO ToJson should cast key to string in order to recover it here
                T k;
                FromString(it.key(), k);
                FromJson(it.value(), map[k]);
            }
        }
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

        template <typename T, typename>
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
                            //  PRINT(property.name);

                             // set the value to the member
                             // you can also replace `asAny` by `fromJson` to recursively serialize
                             FromJson(j[property.name], object.*(property.member));
                             //  object.*(property.member) = j[property.name].template get<Type>();
                             //  object.*(property.member) = JsonFunction::fromJson<Type>(data[property.name]);
                             // Or using streaming
                             // stream >> object.*(property.member);
                         });
        }
    }  // namespace Core
}  // namespace vEngine