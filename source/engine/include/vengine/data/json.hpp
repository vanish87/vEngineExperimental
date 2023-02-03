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
#include <vengine/rendering/mesh_renderer_component.hpp>
#include <vengine/core/mesh_component.hpp>
#include <vengine/core/light.hpp>
#include <vengine/core/light_component.hpp>
#include <vengine/core/camera_component.hpp>
#include <vengine/core/transform_component.hpp>
#include <vengine/core/scene.hpp>
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

        VENGINE_API void SaveJson(const json& j, const std::filesystem::path& path);
        VENGINE_API std::filesystem::path GameObjectToPath(const GameObjectDescriptor& desc);
        VENGINE_API json LoadJson(const std::filesystem::path path);
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

        template <typename T, typename = std::enable_if_t<std::is_same<T, Core::GameObjectType>::value, T>>
        const Core::GameObjectType FromString(const std::string& obj);
    }  // namespace Core
}  // namespace vEngine

#include <vengine/data/to_json.inc>
#include <vengine/data/from_json.inc>
#include <vengine/data/from_to_string.inc>

#ifdef _MSC_VER
    #pragma warning(pop)
#endif

#endif /* _VENGINE_DATA_JSON_HPP */
