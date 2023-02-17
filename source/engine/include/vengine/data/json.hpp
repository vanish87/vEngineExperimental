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

#include <unordered_map>
#include <fstream>

#include <engine.hpp>
#include <external/json.hpp>

#include <vengine/core/game_object.hpp>
#include <vengine/rendering/data_struct.hpp>
#include <vengine/rendering/pipeline_state.hpp>
#include <vengine/rendering/mesh_renderer_component.hpp>
#include <vengine/core/mesh_component.hpp>
#include <vengine/core/light.hpp>
#include <vengine/core/light_component.hpp>
#include <vengine/core/camera_component.hpp>
#include <vengine/core/transform_component.hpp>
#include <vengine/core/scene.hpp>
#include <vengine/core/resource_manager.hpp>
#include <vengine/rendering/material.hpp>
#include <vengine/rendering/texture.hpp>

#include <vengine/animation/animation_clip.hpp>
#include <vengine/animation/animator.hpp>
#include <vengine/animation/animator_component.hpp>
#include <vengine/animation/joint.hpp>

namespace vEngine
{
    namespace Core
    {
        using json = nlohmann::json;
        
        template <class T>
        struct is_shared_ptr : std::false_type { };

        template <class T>
        struct is_shared_ptr<std::shared_ptr<T>> : std::true_type { };

        template <typename T>
        struct is_basic_json_type
        {
                static constexpr auto value = std::is_arithmetic<T>::value || std::is_same<T, std::string>::value;
        };

        VENGINE_API void SaveJson(const json& j, const std::filesystem::path path);
        VENGINE_API const json LoadJson(const std::filesystem::path path);

        VENGINE_API json ToJson(const std::filesystem::path& path);
        VENGINE_API json ToJson(const UUID& uuid);
        VENGINE_API json ToJson(const GameObjectType& go_type);
        VENGINE_API json ToJson(const Rendering::ShaderType& shader_type);
        VENGINE_API json ToJson(const std::vector<char>& vector);

        template <typename T, typename = std::enable_if_t<is_basic_json_type<T>::value, T>, typename = void>
        json ToJson(const T& obj);

        template <typename T>
        json ToJson(const std::weak_ptr<T>& ptr);

        template <typename T>
        json ToJson(const std::shared_ptr<T>& ptr);

        template <typename T>
        json ToJson(const std::vector<T>& vector);

        template <typename T>
        json ToJson(const std::list<T>& list);

        template <typename T, typename S>
        json ToJson(const std::unordered_map<T, S>& umap);

        template <typename T, int N>
        json ToJson(const std::array<T, N>& arr);

        template <typename T, int N>
        json ToJson(const Vector<T, N>& vector);

        template <typename T, int M, int N>
        json ToJson(const Matrix<T, M, N>& matrix);

        template <typename T, typename = std::enable_if_t<!is_basic_json_type<T>::value, T>>
        json ToJson(const T& obj);

        VENGINE_API void FromJson(const json& j, std::filesystem::path& path);
        VENGINE_API void FromJson(const json& j, UUID& uuid);
        VENGINE_API void FromJson(const json& j, GameObjectType& go_type);
        VENGINE_API void FromJson(const json& j, Rendering::ShaderType& shader_type);
        VENGINE_API void FromJson(const json& j, std::vector<char>& vector);

        template <typename T, typename = std::enable_if_t<is_basic_json_type<T>::value, T>, typename = void>
        void FromJson(const json& j, T& obj);

        template <typename T>
        void FromJson([[maybe_unused]] const json& j, [[maybe_unused]] std::weak_ptr<T>& ptr);

        template <typename T>
        void FromJson(const json& j, std::shared_ptr<T>& ptr);

        template <typename T>
        void FromJson(const json& j, std::vector<T>& vector);

        template <typename T>
        void FromJson(const json& j, std::list<T>& list);

        template <typename T, typename S>
        void FromJson(const json& j, std::unordered_map<T, S>& map);

        template <typename T, int N>
        void FromJson(const json& j, Vector<T, N>& vector);

        template <typename T, int M, int N>
        void FromJson(const json& j, Matrix<T, M, N>& matrix);

        template <typename T, int N>
        void FromJson(const json& j, std::array<T, N>& arr);

        template <typename T, typename = std::enable_if_t<!is_basic_json_type<T>::value, T>>
        void FromJson(const json& j, T& object);

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
        Rendering::ShaderType FromString(const std::string& obj);

        template <typename T, typename = std::enable_if_t<std::is_same<T, GameObjectType>::value, T>>
        std::string ToString(const GameObjectType& obj);

        template <typename T, typename = std::enable_if_t<std::is_same<T, Core::GameObjectType>::value, T>>
        Core::GameObjectType FromString(const std::string& obj);
    }  // namespace Core
}  // namespace vEngine

#include <vengine/data/from_to_string.inc>
#include <vengine/data/to_json.inc>
#include <vengine/data/from_json.inc>

#endif /* _VENGINE_DATA_JSON_HPP */
