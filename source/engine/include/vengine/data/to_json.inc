
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
            #define CASE_AND_SAVE(etype, type)                                                     \
                case etype:                                                                        \
                {                                                                                  \
                    auto sub = std::dynamic_pointer_cast<type>(go);                                \
                    ResourceManager::GetInstance().UpdateReferencePath(go);                        \
                    auto path = ResourceManager::GetInstance().GetGameObjectPath(go->descriptor_); \
                    ResourceManager::GetInstance().SaveJson(ToJson(*sub.get()), path);             \
                }                                                                                  \
                break;

            auto go = std::dynamic_pointer_cast<GameObject>(ptr);
            
            auto type = go->descriptor_.type;
            if (type == GameObjectType::Component) CHECK_AND_ASSERT(false, "Cannot create component without game object type");
            if (type == GameObjectType::Renderer) CHECK_AND_ASSERT(false, "Cannot create component without game object type");
            if (type == GameObjectType::RendererComponent) CHECK_AND_ASSERT(false, "Cannot create component without game object type");
            switch (type)
            {
                CASE_AND_SAVE(GameObjectType::GameObject, GameObject);
                CASE_AND_SAVE(GameObjectType::GameNode, GameNode);
                CASE_AND_SAVE(GameObjectType::Transform, Transform);
                CASE_AND_SAVE(GameObjectType::TransformComponent, TransformComponent);
                CASE_AND_SAVE(GameObjectType::Camera, Camera);
                CASE_AND_SAVE(GameObjectType::CameraComponent, CameraComponent);
                CASE_AND_SAVE(GameObjectType::Light, Light);
                CASE_AND_SAVE(GameObjectType::LightComponent, CameraComponent);
                CASE_AND_SAVE(GameObjectType::Mesh, Mesh);
                CASE_AND_SAVE(GameObjectType::MeshComponent, MeshComponent);
                CASE_AND_SAVE(GameObjectType::Scene, Scene);

                // CASE_AND_SAVE(GameObjectType::Serializer, Data::Serializer);

                CASE_AND_SAVE(GameObjectType::MeshRenderer, Rendering::MeshRenderer);
                CASE_AND_SAVE(GameObjectType::MeshRendererComponent, Rendering::MeshRendererComponent);
                CASE_AND_SAVE(GameObjectType::Material, Rendering::Material);
                CASE_AND_SAVE(GameObjectType::Texture, Rendering::Texture);
                CASE_AND_SAVE(GameObjectType::PipelineState, Rendering::PipelineState);
                CASE_AND_SAVE(GameObjectType::Shader, Rendering::Shader);


                CASE_AND_SAVE(GameObjectType::Bone, Animation::Bone);
                CASE_AND_SAVE(GameObjectType::BoneComponent, Animation::BoneComponent);
                CASE_AND_SAVE(GameObjectType::Joint, Animation::Joint);
                CASE_AND_SAVE(GameObjectType::AnimationClip, Animation::AnimationClip);
                CASE_AND_SAVE(GameObjectType::Animator, Animation::Animator);
                CASE_AND_SAVE(GameObjectType::AnimatorComponent, Animation::AnimatorComponent);
                default:
                    PRINT(ToString(type));
                    NOT_IMPL_ASSERT;
                    break;
            }

            // only return GameObject info(as a reference) here
            return ToJson(*go.get());

            #undef CASE_AND_SAVE
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
                value[ToString<T>(e.first)] = ToJson(e.second);
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