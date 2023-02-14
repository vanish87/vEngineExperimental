
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
        void FromJson([[maybe_unused]] const json& j, [[maybe_unused]] std::weak_ptr<T>& ptr)
        {
            // UNUSED_PARAMETER(j);
            // UNUSED_PARAMETER(ptr);

            // auto shared = std::shared_ptr<T>();
            // FromJson(j, shared);
            // ptr = shared;
        }

        template <typename T>
        std::shared_ptr<T> CreateAndLoadByDesc(const GameObjectDescriptor& desc)
        {
            #define CASE_AND_CREATE(ptr, etype, type)                   \
                case etype:                                             \
                {                                                       \
                    auto go = GameObjectFactory::Create<etype, type>(); \
                    FromJson(LoadJson(path), *go.get());                \
                    ptr = go;                                           \
                }                                                       \
                break;

            #define CASE_AND_CREATE_ARG(ptr, etype, type, args)             \
                case etype:                                                 \
                {                                                           \
                    auto go = GameObjectFactory::Create<etype, type>(args); \
                    FromJson(LoadJson(path), *go.get());                    \
                    ptr = go;                                               \
                }                                                           \
                break;

            GameObjectSharedPtr shared;
            auto path = ResourceManager::GetInstance().GetGameObjectPath(desc);

            switch (desc.type)
            {
                CASE_AND_CREATE(shared, GameObjectType::GameObject, GameObject);
                CASE_AND_CREATE(shared, GameObjectType::GameNode, GameNode);
                // CASE_AND_CREATE(shared, GameObjectType::Component, GameNode);
                CASE_AND_CREATE(shared, GameObjectType::Transform, Transform);
                CASE_AND_CREATE(shared, GameObjectType::TransformComponent, TransformComponent);
                CASE_AND_CREATE(shared, GameObjectType::Camera, Camera);
                CASE_AND_CREATE(shared, GameObjectType::CameraComponent, CameraComponent);
                CASE_AND_CREATE(shared, GameObjectType::Light, Light);
                CASE_AND_CREATE(shared, GameObjectType::LightComponent, LightComponent);
                CASE_AND_CREATE(shared, GameObjectType::Mesh, Mesh);
                CASE_AND_CREATE(shared, GameObjectType::MeshComponent, MeshComponent);
                CASE_AND_CREATE(shared, GameObjectType::Scene, Scene);
                
                // CASE_AND_CREATE(shared, GameObjectType::Serializer, Data::Serializer);


                // CASE_AND_CREATE(shared, GameObjectType::Renderer, Rendering::Renderer);
                CASE_AND_CREATE(shared, GameObjectType::MeshRenderer, Rendering::MeshRenderer);
                CASE_AND_CREATE(shared, GameObjectType::MeshRendererComponent, Rendering::MeshRendererComponent);
                CASE_AND_CREATE(shared, GameObjectType::Material, Rendering::Material);
                CASE_AND_CREATE_ARG(shared, GameObjectType::Texture, Rendering::Texture, Rendering::TextureDescriptor::Default());
                CASE_AND_CREATE_ARG(shared, GameObjectType::PipelineState, Rendering::PipelineState, Rendering::PipelineStateDescriptor::Default());
                CASE_AND_CREATE(shared, GameObjectType::Shader, Rendering::Shader);

                CASE_AND_CREATE(shared, GameObjectType::Bone, Animation::Bone);
                CASE_AND_CREATE(shared, GameObjectType::BoneComponent, Animation::BoneComponent);
                CASE_AND_CREATE(shared, GameObjectType::Joint, Animation::Joint);
                CASE_AND_CREATE(shared, GameObjectType::AnimationClip, Animation::AnimationClip);
                CASE_AND_CREATE(shared, GameObjectType::Animator, Animation::Animator);
                CASE_AND_CREATE(shared, GameObjectType::AnimatorComponent, Animation::AnimatorComponent);
                default:
                    NOT_IMPL_ASSERT;
                    break;
            }

            return std::dynamic_pointer_cast<T>(shared);

            #undef CASE_AND_CREATE
            #undef CASE_AND_CREATE_ARG
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
            // ptr = ResourceManager::GetInstance().Load(desc));
            // if(ptr != nullptr) return;
            // CHECK_ASSERT(ptr == nullptr);

            ptr = CreateAndLoadByDesc<T>(desc);
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

        template <typename T, typename S>
        void FromJson(const json& j, std::unordered_map<T, S>& map)
        {
            for (auto it = j.begin(); it != j.end(); ++it)
            {
                // TODO ToJson should cast key to string in order to recover it here
                auto k = FromString<T>(it.key());
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