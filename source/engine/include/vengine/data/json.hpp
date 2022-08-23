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
#include <fstream>

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
        void SaveJson(const nlohmann::json& j, const std::filesystem::path& path);
        std::filesystem::path GameObjectToPath(const GameObjectDescription& desc);
        nlohmann::json ParseJson(const std::filesystem::path path);
        template <std::size_t I, class T, typename Src>
        auto CastByType(std::shared_ptr<Src> ptr);

        template <typename T>
        auto GetTypeString(std::shared_ptr<T> prt);

        template <typename T, typename = std::enable_if_t<std::is_integral<T>::value, T>>
        std::string ToString(const T& obj);

        template <typename T, typename = std::enable_if_t<std::is_integral<T>::value, T>>
        const T FromString(const std::string& obj);

        template <typename T, typename = std::enable_if_t<std::is_same<T, std::string>::value, T>>
        std::string ToString(const std::string& obj);

        template <typename T, typename = std::enable_if_t<std::is_same<T, std::string>::value, T>>
        const std::string FromString(const std::string& obj);

        template <typename T, typename = std::enable_if_t<std::is_same<T, Core::UUID>::value, T>>
        std::string ToString(const Core::UUID& uuid);

        template <typename T, typename = std::enable_if_t<std::is_same<T, Core::UUID>::value, T>>
        const Core::UUID FromString(const std::string& obj);

        template <typename T, typename = std::enable_if_t<std::is_same<T, Rendering::ShaderType>::value, T>>
        std::string ToString(const Rendering::ShaderType& obj);

        template <typename T, typename = std::enable_if_t<std::is_same<T, Rendering::ShaderType>::value, T>>
        const Rendering::ShaderType FromString(const std::string& obj);

        template <typename T, typename = std::enable_if_t<std::is_same<T, GameObjectType>::value, T>>
        std::string ToString(const GameObjectType& obj);

        template <class T>
        struct is_shared_ptr : std::false_type { };

        template <class T>
        struct is_shared_ptr<std::shared_ptr<T>> : std::true_type { };


        template <typename T>
        struct is_basic_json_type
        {
                static constexpr auto value = std::is_arithmetic<T>::value || std::is_same<T, std::string>::value;
        };

        template <typename T, typename = std::enable_if_t<is_basic_json_type<T>::value, T>, typename = void>
        nlohmann::json ToJson(const T& obj);

        template <typename T, typename = std::enable_if_t<!is_basic_json_type<T>::value, T>>
        nlohmann::json ToJson(const T& obj);

        template <typename T>
        nlohmann::json ToJson(const std::weak_ptr<T>& ptr);

        template <typename T>
        nlohmann::json ToJson(const std::shared_ptr<T>& ptr);

        template <>
        nlohmann::json ToJson(const std::filesystem::path& path);

        template <>
        nlohmann::json ToJson(const UUID& uuid);

        template <>
        nlohmann::json ToJson(const Rendering::ShaderType& shader_type);

        template <>
        nlohmann::json ToJson(const GameObjectType& go_type);

        template <typename T>
        nlohmann::json ToJson(const std::vector<T>& vector);

        template <>
        nlohmann::json ToJson(const std::vector<char>& vector);

        template <typename T>
        nlohmann::json ToJson(const std::list<T>& list);

        template <typename T, typename S>
        nlohmann::json ToJson(const std::unordered_map<T, S>& umap);

        template <typename T, int N>
        nlohmann::json ToJson(const std::array<T, N>& obj);

        template <typename T, int N>
        nlohmann::json ToJson(const Vector<T, N>& vector);

        template <typename T, int M, int N>
        nlohmann::json ToJson(const Matrix<T, M, N>& matrix);

        template <typename T, typename = std::enable_if_t<is_basic_json_type<T>::value, T>, typename = void>
        void FromJson(const nlohmann::json& j, T& obj);

        template <typename T, typename = std::enable_if_t<!is_basic_json_type<T>::value, T>>
        void FromJson(const nlohmann::json& j, T& object);

        template <>
        void FromJson(const nlohmann::json& j, UUID& uuid);

        template <>
        void FromJson(const nlohmann::json& j, std::filesystem::path& path);

        template <>
        void FromJson(const nlohmann::json& j, GameObjectType& go_type);

        template <>
        void FromJson(const nlohmann::json& j, Rendering::ShaderType& shader_type);

        template <typename T>
        void FromJson(const nlohmann::json& j, std::weak_ptr<T>& ptr);

        template <typename T>
        void FromJson(const nlohmann::json& j, std::shared_ptr<T>& ptr);

        template <typename T>
        void FromJson(const nlohmann::json& j, std::vector<T>& vector);

        template <typename T>
        void FromJson(const nlohmann::json& j, std::list<T>& list);

        template <typename T, typename S>
        void FromJson(const nlohmann::json& j, std::unordered_map<T, S>& map);

        template <typename T, int N>
        void FromJson(const nlohmann::json& j, Vector<T, N>& vector);

        template <typename T, int M, int N>
        void FromJson(const nlohmann::json& j, Matrix<T, M, N>& matrix);

        template <typename T, int N>
        void FromJson(const nlohmann::json& j, std::array<T, N>& arr);
    }  // namespace Core
}  // namespace vEngine

#include <vengine/data/from_json.inc>
#include <vengine/data/to_json.inc>
#include <vengine/data/from_to_string.inc>

#ifdef _MSC_VER
    #pragma warning(pop)
#endif

#endif /* _VENGINE_DATA_JSON_HPP */
