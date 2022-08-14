/// \file json.hpp
/// \brief Head file for json
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_DATA_JSON_HPP
#define _VENGINE_DATA_JSON_HPP

#pragma once

#ifdef _MSC_VER
    #pragma warning(push)
    #pragma warning(disable : 4505) 
#endif

#include <unordered_map>

#include <engine.hpp>
#include <external/json.hpp>

#include <vengine/core/game_object.hpp>
#include <vengine/rendering/data_struct.hpp>
#include <vengine/rendering/pipeline_state.hpp>
#include <vengine/core/mesh_renderer_component.hpp>
#include <vengine/core/mesh_component.hpp>
#include <vengine/core/camera_component.hpp>
#include <vengine/core/transform_component.hpp>
#include <vengine/core/scene.hpp>
#include <vengine/rendering/material.hpp>
#include <vengine/rendering/texture.hpp>

#include <vengine/animation/animation_clip.hpp>
#include <vengine/animation/animator.hpp>
#include <vengine/animation/joint.hpp>

namespace vEngine
{
    namespace Core
    {
        template <typename T>
        struct is_basic_json_type
        {
                static constexpr auto value = std::is_arithmetic<T>::value || std::is_same<T, std::string>::value;
        };
        template <typename T, typename = std::enable_if_t<std::is_integral<T>::value, T>>
        std::string ToString(const T& obj)
        {
            return std::to_string(obj);
        }
        template <typename T, typename = std::enable_if_t<std::is_integral<T>::value, T>>
        const T FromString(const std::string& obj)
        {
            return std::stoi(obj);
        }
        template <typename T, typename = std::enable_if_t<std::is_same<T, std::string>::value, T>>
        std::string ToString(const std::string& obj)
        {
            return obj;
        }
        template <typename T, typename = std::enable_if_t<std::is_same<T, std::string>::value, T>>
        const std::string FromString(const std::string& obj)
        {
            return obj;
        }
        template <typename T, typename = std::enable_if_t<std::is_same<T, Core::UUID>::value, T>>
        std::string ToString(const Core::UUID& uuid)
        {
            return ToString(uuid.AsUint());
        }
        template <typename T, typename = std::enable_if_t<std::is_same<T, Core::UUID>::value, T>>
        const Core::UUID FromString(const std::string& obj)
        {
            return Core::UUID(std::stoi(obj));
        }
        template <typename T, typename = std::enable_if_t<std::is_same<T, Rendering::ShaderType>::value, T>>
        std::string ToString(const Rendering::ShaderType& obj)
        {
            switch (obj)
            {
            case Rendering::ShaderType::VS: return "VS";
            case Rendering::ShaderType::GS: return "GS";
            case Rendering::ShaderType::PS: return "PS";
            case Rendering::ShaderType::CS: return "CS";
            default:
                break;
            }
            NOT_IMPL_ASSERT;
            return "NOT DEFINED";
        }
        template <typename T, typename = std::enable_if_t<std::is_same<T, GameObjectType>::value, T>>
        std::string ToString(const GameObjectType& obj)
        {
            switch (obj)
            {
            case GameObjectType::Raw: return "Raw";
            case GameObjectType::GameNode: return "GameNode";
            case GameObjectType::Component: return "Component";
            case GameObjectType::Camera: return "Camera";
            case GameObjectType::AnimationClip: return "AnimationClip";
            case GameObjectType::Asset: return "Asset";
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
        // public interface of ToJson
        template <typename T>
        static void ToJson(nlohmann::json& j, const T& obj)
        {
            j = ToJson(obj);
        }

        template <typename T, typename = std::enable_if_t<is_basic_json_type<T>::value, T>, typename = void>
        nlohmann::json ToJson(const T& obj)
        {
            return nlohmann::json(obj);
        }

        template <typename T, typename = std::enable_if_t<!is_basic_json_type<T>::value, T>>
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
        template <typename T>
        nlohmann::json ToJson(const std::weak_ptr<T>& ptr, bool as_reference = true)
        {
            auto shared = ptr.lock();
            if(shared != nullptr) return ToJson(shared, as_reference);
            return nlohmann::json();
        }
        template <typename T>
        nlohmann::json ToJson(const std::shared_ptr<T>& ptr, bool as_reference = true)
        {
            nlohmann::json value;

            if(!as_reference)
            {
                using type_list = std::tuple<Rendering::Shader, Rendering::Material, Scene, Transform, TransformComponent, Mesh, MeshComponent, MeshRenderer, Rendering::MeshRendererComponent, Camera,
                                             CameraComponent, Rendering::PipelineState, Rendering::Texture, Animation::AnimationClip, Animation::Joint, Animation::Bone, GameNode>;
                constexpr auto nlist = std::tuple_size<type_list>::value;
                for_sequence(std::make_index_sequence<nlist>{},
                             [&](auto i)
                             {
                                 auto p = CastByType<i, type_list>(ptr);
                                 if (value.is_null() && p != nullptr)
                                 {
                                     //  value["data_type"] = GetTypeString(p);
                                     //  value["data"] = ToJson(*p.get());
                                     value = ToJson(*p.get());
                                 }
                             });
            }
            if (!value.is_null()) return value;


            auto go = std::dynamic_pointer_cast<GameObject>(ptr);

            // TODO Use context map for shared ptr
            // save uuid and/or other necessary description with json value
            // so that FromJson can find/create objects from xx factory class

            // value["data_type"] = GetTypeString(ptr);
            // value["data"] = ToJson(*ptr.get());
            value = ToJson(*go.get());
            return value;
        }
        // template <typename T, typename = std::enable_if_t<std::is_base_of<GameObject, T>::value, T>, typename = void, typename = void>
        // nlohmann::json ToJson(const T& go)
        // {
        //     UNUSED_PARAMETER(go);
        //     nlohmann::json value;
        //     return value;
        //     // return ToJson(ptr);
        // }
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

        template <typename T, typename = std::enable_if_t<!is_basic_json_type<T>::value, T>>
        static void FromJson(const nlohmann::json& j, T& object)
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

        template <typename T, typename = std::enable_if_t<is_basic_json_type<T>::value, T>, typename = void>
        void FromJson(const nlohmann::json& j, T& obj)
        {
            obj = j.get<T>();
        }
        // template <typename T, typename = std::enable_if_t<std::is_same<T, GameObjectType>::value, T>, typename = void>
        template <>
        void FromJson(const nlohmann::json& j, GameObjectType& go_type)
        {
            UNUSED_PARAMETER(j);
            UNUSED_PARAMETER(go_type);
            // return nlohmann::json(ToString<GameObjectType>(go_type));
        }
        template <typename T>
        void FromJson(const nlohmann::json& j, std::shared_ptr<T>& ptr)
        {
            auto desc = GameObjectDescription();
            // FromJson(j["data"], *v);

            FromJson(j["description"], desc);

            auto v = new T();
            FromJson(j, *v);
            ptr.reset(v);
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
            auto idx = 0;
            for (auto it = j.begin(); it != j.end(); ++it)
            {
                FromJson(*it, vector[idx++]);
            }
        }
        template <typename T, int M, int N>
        void FromJson(const nlohmann::json& j, Matrix<T, M, N>& matrix)
        {
            auto idx = 0;
            for (auto it = j.begin(); it != j.end(); ++it)
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

// #ifdef _MSC_VER
//     #pragma warning(pop)
// #endif

#endif /* _VENGINE_DATA_JSON_HPP */
