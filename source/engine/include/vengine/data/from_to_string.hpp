#ifndef _VENGINE_DATA_FROM_TO_STRING_HPP
#define _VENGINE_DATA_FROM_TO_STRING_HPP

#include <string>
#include <engine.hpp>
#include <vengine/rendering/data_struct.hpp>

namespace vEngine
{
    namespace Core
    {
        template <typename T, typename = std::enable_if_t<std::is_integral<T>::value, T>>
        void ToString(const T& obj, std::string& to)
        {
            to = std::to_string(obj);
        }

        template <typename T, typename = std::enable_if_t<std::is_integral<T>::value, T>>
        void FromString(const std::string& obj, T& to)
        {
            to = std::stoi(obj);
        }

        void ToString(const std::string& obj, std::string& to);
        void FromString(const std::string& obj, std::string& to);

        void ToString(const Rendering::ShaderType& obj, std::string& to);
        void FromString(const std::string& obj, Rendering::ShaderType& to);

        void ToString(const GameObjectType& obj, std::string& to);
        void FromString(const std::string& obj, Core::GameObjectType& to);

    }  // namespace Core
}  // namespace vEngine


#endif /* _VENGINE_DATA_FROM_TO_STRING_HPP */