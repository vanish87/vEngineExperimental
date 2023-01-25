
#include <vengine/data/class_foo.hpp>
#include <vengine/core/game_object_factory.hpp>
    

//TODO use Default for better obj creation: auto go = type_name::Default();                                 
#define FROM_JSON_BY_DESC(ptr, desc, type_name, template_name)      \
if (ToString(desc.type) == typeid(type_name).name())                \
{                                                                   \
    auto go = GameObjectFactory::Create<type_name>();               \
    auto json = LoadJson(GameObjectToPath(desc));                   \
    FromJson(json, *go.get());                                      \
    ptr = std::dynamic_pointer_cast<template_name>(go);             \
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
            auto data = j.get<std::string>();
            go_type = FromString<GameObjectType>(data);
            // NOT_IMPL_ASSERT;
            // UNUSED_PARAMETER(j);
            // UNUSED_PARAMETER(go_type);
            // return json(ToString<GameObjectType>(go_type));
        }
        template <>
        void FromJson(const json& j, Rendering::ShaderType& shader_type)
        {
            auto data = j.get<std::string>();
            shader_type = FromString<Rendering::ShaderType>(data);
            // NOT_IMPL_ASSERT;
            // UNUSED_PARAMETER(j);
            // UNUSED_PARAMETER(shader_type);
            // return json(ToString<GameObjectType>(go_type));
        }

        template <typename T>
        void FromJson(const json& j, std::weak_ptr<T>& ptr)
        {
            UNUSED_PARAMETER(j);
            UNUSED_PARAMETER(ptr);

            // auto shared = std::shared_ptr<T>();
            // FromJson(j, shared);
            // ptr = shared;
        }
        template <std::size_t I, class T, typename S>
        bool HandleByType(std::shared_ptr<S>& ptr, const GameObjectDescriptor& desc)
        {
            using Type = typename std::tuple_element_t<I, T>;
            // if(std::is_same<T, Type>::value)
            if(typeid(Type).name() == ToString(desc.type))
            {
                FROM_JSON_BY_DESC(ptr, desc, Type, S);
                return true;
            }
            return false;
        }

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

        template <typename T>
        std::shared_ptr<T> CreateAndLoadByDesc(const GameObjectDescriptor& desc)
        {
            // if (type == "class vEngine::Core::CameraComponent") return Create<CameraComponent>();
            // if (type == "class vEngine::Core::TransformComponent") return Create<TransformComponent>();
            // if (type == "class vEngine::Core::Scene") return Create<Scene>();
            // if (type == "class vEngine::Core::GameNode") return Create<GameNode>();

            // auto type = desc.type;

            // using type_list = std::tuple<ClassBar, ClassFoo>;
            using type_list =
                std::tuple<Rendering::Shader, Rendering::Material, Scene, Transform, TransformComponent, Mesh, MeshComponent, Rendering::MeshRenderer, Rendering::MeshRendererComponent, Camera, CameraComponent,
                           Rendering::PipelineState, Rendering::Texture, Animation::AnimationClip, Animation::Joint, Animation::Bone, Animation::BoneComponent, GameNode, ClassFoo, ClassBar>;

            GameObjectSharedPtr shared;
            // auto handled = false;

            auto path = GameObjectToPath(desc);
            PRINT("Path " << path);
            // auto type = desc.type;

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

            // constexpr auto nlist = std::tuple_size<type_list>::value;
            // for_sequence(std::make_index_sequence<nlist>{},
            //              [&](auto i)
            //              {
            //                 if(!handled)
            //                 {
            //                     handled = HandleByType<i, type_list>(shared, desc);
            //                     // PRINT(desc.type << " " << (handled ? "Handled" : "Skiped"));
            //                 }
            //              });
            // FROM_JSON_BY_DESC(desc, ClassFoo, T);
            // FROM_JSON_BY_DESC(desc, ClassBar, T);

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
            return std::dynamic_pointer_cast<T>(shared);
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
            FromJson(j["game_object_meta"], desc);

            // 1. find by uuid
            // ptr = GameObjectFactory::Find<T>(desc);
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
        template <>
        void FromJson(const json& j, std::vector<char>& vector)
        {
            vector.clear();
            auto data = j.get<std::string>();
            for (const auto& it : data)
            {
                vector.push_back(it);
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