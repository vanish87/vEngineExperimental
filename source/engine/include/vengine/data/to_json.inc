
namespace vEngine
{
    namespace Core
    {
        template <typename T, typename, typename>
        json ToJson(const T& obj)
        {
            return json(obj);
        }

        template <typename T>
        json ToJson(const std::weak_ptr<T>& ptr)
        {
            auto shared = ptr.lock();
            return ToJson(shared);
        }


        template <typename T>
        json ToJson(const std::shared_ptr<T>& ptr)
        {

            auto go = std::dynamic_pointer_cast<GameObject>(ptr);
            if (go == nullptr) return json();
            // only return GameObject info(as a reference) here
            return ToJson(*go.get());
        }

        template <typename T>
        json ToJson(const std::vector<T>& vector)
        {
            json value;
            auto id = 0;
            for (const auto& e : vector)
            {
                value[id++] = ToJson(e);
            }
            return value;
        }

        template <typename T>
        json ToJson(const std::list<T>& list)
        {
            json value;
            auto id = 0;
            for (const auto& e : list)
            {
                value[id++] = ToJson(e);
            }
            return value;
        }

        template <typename T, typename S>
        json ToJson(const std::unordered_map<T, S>& umap)
        {
            json value;
            for (const auto& e : umap)
            {
                std::string k;
                ToString(e.first, k);
                value[k] = ToJson(e.second);
            }
            return value;
        }

        template <typename T, int N>
        json ToJson(const std::array<T, N>& arr)
        {
            UNUSED_PARAMETER(arr);
            NOT_IMPL_ASSERT;
            // static_assert(false, "Should used vengine data types for serializer");
            return json();
        }
        template <typename T, int N>
        json ToJson(const Vector<T, N>& vector)
        {
            json value;
            auto id = 0;
            for (const auto& e : vector)
            {
                value[id++] = ToJson(e);
            }
            return value;
        }
        template <typename T, int M, int N>
        json ToJson(const Matrix<T, M, N>& matrix)
        {
            json value;
            auto id = 0;
            for (const auto& row : matrix)
            {
                value[id++] = ToJson(row);
            }
            return value;
        }
        template <typename T, typename>
        json ToJson(const T& obj)
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

    }  // namespace Core
}  // namespace vEngine