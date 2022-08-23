
namespace vEngine
{
    namespace Core
    {
        template <typename T, class... Args>
        go_shared_ptr<T> go_make_shared(Args&&... args)
        {
            static_assert(std::is_base_of<GameObject, T>::value, "T must derived from GameObject");
            auto go = new T(std::forward<Args>(args)...);
            go_shared_ptr<T> go_ptr;
            go_ptr.reset(go);
            return go_ptr;
        }
        template <typename T, typename, typename>
        nlohmann::json ToJson(const T& obj)
        {
            return nlohmann::json(obj);
        }
        template <typename T, typename>
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
        template <typename T>
        nlohmann::json ToJson(const std::weak_ptr<T>& ptr)
        {
            auto shared = ptr.lock();
            auto go = std::dynamic_pointer_cast<GameObject>(shared);
            if (go != nullptr)
            {
                return ToJson(*go.get());
            }
            return nlohmann::json();
        }
        template <typename T>
        nlohmann::json ToJson(const std::shared_ptr<T>& ptr)
        {
            auto content_saved = false;

            using type_list = std::tuple<Rendering::Shader, Rendering::Material, Scene, Transform, TransformComponent, Mesh, MeshComponent, MeshRenderer, Rendering::MeshRendererComponent, Camera,
                                         CameraComponent, Rendering::PipelineState, Rendering::Texture, Animation::AnimationClip, Animation::Joint, Animation::Bone, GameNode, ClassFoo, ClassBar>;
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
        nlohmann::json ToJson(const std::filesystem::path& path)
        {
            return nlohmann::json(path.string());
        }
        template <>
        nlohmann::json ToJson(const UUID& uuid)
        {
            return nlohmann::json(uuid.AsUint());
        }
        template <>
        nlohmann::json ToJson(const Rendering::ShaderType& shader_type)
        {
            return nlohmann::json(ToString<Rendering::ShaderType>(shader_type));
        }
        template <>
        nlohmann::json ToJson(const GameObjectType& go_type)
        {
            return nlohmann::json(ToString<GameObjectType>(go_type));
        }
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
        template <>
        nlohmann::json ToJson(const std::vector<char>& vector)
        {
            return nlohmann::json(std::string(vector.begin(), vector.end()));
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

        void SaveJson(const nlohmann::json& j, const std::filesystem::path& path)
        {
            std::ofstream outfile(path.string());
            outfile << std::setw(2) << j << std::endl;
            outfile.flush();
            outfile.close();
        }
        std::filesystem::path GameObjectToPath(const GameObjectDescription& desc)
        {
            auto config = Context::GetInstance().CurrentConfigure();
            auto path = config.resource_bin;
            auto context_name = config.context_name;
            // auto gn = std::dynamic_pointer_cast<GameNode>(go);
            // if(gn != nullptr)
            // {
            //     while(gn != nullptr)
            //     {
            //         path /= gn->description_.name;
            //     }
            // }

            auto name = desc.name;
            auto type = desc.type;

            auto file_name = std::to_string(desc.uuid.AsUint()) + "_" + name + "_" + type + ".json";

            std::string illegal = ":\"\'<>%$*&+ ";
            for (auto c : illegal)
            {
                std::replace(file_name.begin(), file_name.end(), c, '_');
            }

            return path / context_name / file_name;
        }
        nlohmann::json ParseJson(const std::filesystem::path path)
        {
            std::ifstream file(path.string());
            auto j = nlohmann::json::parse(file);
            file.close();
            return j;
        }
        template <std::size_t I, class T, typename Src>
        auto CastByType(std::shared_ptr<Src> ptr)
        {
            return std::dynamic_pointer_cast<std::tuple_element_t<I, T>>(ptr);
        }
        template <typename T>
        auto GetTypeString(std::shared_ptr<T> prt)
        {
            return typeid(T).name();
        }
        template <typename T, typename>
        std::string ToString(const T& obj)
        {
            return std::to_string(obj);
        }
        template <typename T, typename>
        const T FromString(const std::string& obj)
        {
            return std::stoi(obj);
        }
        template <typename T, typename>
        std::string ToString(const std::string& obj)
        {
            return obj;
        }
        template <typename T, typename>
        const std::string FromString(const std::string& obj)
        {
            return obj;
        }
        template <typename T, typename>
        std::string ToString(const Core::UUID& uuid)
        {
            return ToString(uuid.AsUint());
        }
        template <typename T, typename>
        const Core::UUID FromString(const std::string& obj)
        {
            return Core::UUID(std::stoi(obj));
        }
        template <typename T, typename>
        std::string ToString(const Rendering::ShaderType& obj)
        {
            switch (obj)
            {
                case Rendering::ShaderType::VS:
                    return "VS";
                case Rendering::ShaderType::GS:
                    return "GS";
                case Rendering::ShaderType::PS:
                    return "PS";
                case Rendering::ShaderType::CS:
                    return "CS";
                default:
                    break;
            }
            NOT_IMPL_ASSERT;
            return "NOT DEFINED";
        }
        template <typename T, typename>
        const Rendering::ShaderType FromString(const std::string& obj)
        {
            if (obj == "VS") return Rendering::ShaderType::VS;
            // case Rendering::ShaderType::GS: return "GS";
            // case Rendering::ShaderType::PS: return "PS";
            // case Rendering::ShaderType::CS: return "CS";
            NOT_IMPL_ASSERT;
            return Rendering::ShaderType::VS;
        }
        template <typename T, typename>
        std::string ToString(const GameObjectType& obj)
        {
            switch (obj)
            {
                case GameObjectType::Raw:
                    return "Raw";
                case GameObjectType::GameNode:
                    return "GameNode";
                case GameObjectType::Component:
                    return "Component";
                case GameObjectType::Camera:
                    return "Camera";
                case GameObjectType::AnimationClip:
                    return "AnimationClip";
                case GameObjectType::Asset:
                    return "Asset";
                default:
                    break;
            }
            // NOT_IMPL_ASSERT;
            return "NOT DEFINED";
        }
        // template <typename T, typename = std::enable_if_t<std::is_same<T, std::filesystem::path>::value, T>>
        // std::string ToString(const std::filesystem::path& obj)
        // {
        //     return obj.string();
        // }
    }  // namespace Core
}  // namespace vEngine