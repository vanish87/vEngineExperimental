
namespace vEngine
{
    namespace Core
    {
        template <typename T, typename, typename>
        void FromJson(const nlohmann::json& j, T& obj)
        {
            obj = j.get<T>();
        }

        template <typename T, typename>
        void FromJson(const nlohmann::json& j, T& object)
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
        void FromJson(const nlohmann::json& j, UUID& uuid)
        {
            auto id = j.get<uint64_t>();
            uuid.Set(id);
        }
        template <>
        void FromJson(const nlohmann::json& j, std::filesystem::path& path)
        {
            auto data = j.get<std::string>();
            path = data;
        }
        // template <typename T, typename = std::enable_if_t<std::is_same<T, GameObjectType>::value, T>, typename = void>
        template <>
        void FromJson(const nlohmann::json& j, GameObjectType& go_type)
        {
            NOT_IMPL_ASSERT;
            UNUSED_PARAMETER(j);
            UNUSED_PARAMETER(go_type);
            // return nlohmann::json(ToString<GameObjectType>(go_type));
        }
        template <>
        void FromJson(const nlohmann::json& j, Rendering::ShaderType& shader_type)
        {
            NOT_IMPL_ASSERT;
            UNUSED_PARAMETER(j);
            UNUSED_PARAMETER(shader_type);
            // return nlohmann::json(ToString<GameObjectType>(go_type));
        }

        template <typename T>
        void FromJson(const nlohmann::json& j, std::weak_ptr<T>& ptr)
        {
            UNUSED_PARAMETER(j);
            UNUSED_PARAMETER(ptr);
        }
        template <typename T>
        void FromJson(const nlohmann::json& j, std::shared_ptr<T>& ptr)
        {
            GameObjectDescription desc;
            // FromJson(j["data"], *v);

            FromJson(j["description"], desc);

            // PRINT("Deserialize " << desc.uuid.AsUint() << " " << desc.type);

            // 1. find by uuid
            auto go = GameObjectFactory::FindOrCreate<T>(desc);
            CHECK_ASSERT_NOT_NULL(go);
            ptr = go;

            auto json = ParseJson(GameObjectToPath(desc));
            FromJson(json, *ptr.get());

            PRINT("Load " << go->description_.uuid.AsUint() << " " << desc.type);
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
            for (auto& i : vector)
            {
                FromJson(j, i);
            }
        }
        template <typename T, int M, int N>
        void FromJson(const nlohmann::json& j, Matrix<T, M, N>& matrix)
        {
            auto idx = 0;
            for (const auto& row : matrix)
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