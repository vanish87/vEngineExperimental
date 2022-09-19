
namespace vEngine
{
    namespace Core
    {
        template <typename T, typename = std::enable_if_t<is_basic_json_type<T>::value, T>, typename = void>
        json ToJson(const T& obj)
        {
            return json(obj);
        }
        template <typename T, typename = std::enable_if_t<!is_basic_json_type<T>::value, T>>
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
        template <typename T>
        json ToJson(const std::weak_ptr<T>& ptr)
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
        json ToJson(const std::shared_ptr<T>& ptr)
        {
            auto content_saved = false;

            using type_list = std::tuple<Rendering::Shader, Rendering::Material, Scene, Transform, TransformComponent, Mesh, MeshComponent, MeshRenderer, Rendering::MeshRendererComponent, Camera,
                                         CameraComponent, Rendering::PipelineState, Rendering::Texture, Animation::AnimationClip, Animation::Joint, Animation::Bone, Animation::BoneComponent, GameNode, ClassFoo, ClassBar>;
            constexpr auto nlist = std::tuple_size<type_list>::value;
            for_sequence(std::make_index_sequence<nlist>{},
                         [&](auto i)
                         {
                             auto p = CastByType<i, type_list>(ptr);
                             if (!content_saved && p != nullptr)
                             {
                                 content_saved = true;

                                 auto value = ToJson(*p.get());
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
        template <>
        json ToJson(const std::filesystem::path& path)
        {
            return json(path.string());
        }
        template <>
        json ToJson(const UUID& uuid)
        {
            return json(uuid.AsUint());
        }
        template <>
        json ToJson(const Rendering::ShaderType& shader_type)
        {
            return json(ToString<Rendering::ShaderType>(shader_type));
        }
        template <>
        json ToJson(const GameObjectType& go_type)
        {
            return json(ToString<GameObjectType>(go_type));
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
        template <>
        json ToJson(const std::vector<char>& vector)
        {
            return json(std::string(vector.begin(), vector.end()));
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
                value[ToString<T>(e.first)] = ToJson(e.second);
            }
            return value;
        }
        template <typename T, int N>
        json ToJson(const std::array<T, N>& obj)
        {
            NOT_IMPL_ASSERT;
            static_assert(false, "Should used vengine data types for serializer") UNUSED_PARAMETER(obj);
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

    }  // namespace Core
}  // namespace vEngine