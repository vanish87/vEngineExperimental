/// \file scene.hpp
/// \brief Head file for Scene Node
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_SCENE_HPP
#define _VENGINE_CORE_SCENE_HPP

#pragma once

#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <map>

#include <engine.hpp>
#include <vengine/core/game_node.hpp>
#include <vengine/core/iresource.hpp>
#include <vengine/core/vector.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        // using namespace Rendering;
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class Scene : public GameNode  //, public IResource
        {
            public:
                /// \brief brief constructor description.
                Scene();
                void LoadFile(const std::filesystem::path file_path);

                void Update();
                void Flush();

                /// class variable description
                // int public_variable_;

            public:
                /// \brief A brief function description.
                ///
                /// \param p1 Description for p1.
                /// \param p2 Description for p2.
                /// \return Description for return value.
                // int GetVariable(int p1, float p2);
                void AddToSceneNode(const GameNodeSharedPtr new_node, const GameNodeSharedPtr game_node = nullptr);
                void AddTestNode();
                void Print();

            private:
        };

    }  // namespace Core
}  // namespace vEngine

// Sample implementation of a json-like data structure. It is only there for the example to compile and actually produce a testable output
namespace Json
{
    struct Value;

    struct ValueData
    {
            std::map<std::string, Value> subObject;
            std::string string;
            int number = 0;
            vEngine::Core::float4 numberf;
    };

    struct Value
    {
            ValueData data;

            Value& operator[](std::string name)
            {
                return data.subObject[std::move(name)];
            }

            const Value& operator[](std::string name) const
            {
                auto it = data.subObject.find(std::move(name));

                if (it != data.subObject.end())
                {
                    return it->second;
                }

                throw;
            }

            Value& operator=(std::string value)
            {
                data.string = value;
                return *this;
            }

            Value& operator=(int value)
            {
                data.number = value;
                return *this;
            }
            Value& operator=(vEngine::Core::float4 value)
            {
                data.numberf = value;
                return *this;
            }
    };

    template <typename T>
    T& asAny(Value&);
    template <typename T>
    const T& asAny(const Value&);


}  // namespace Json
// sequence for
template <typename T, T... S, typename F>
constexpr void for_sequence(std::integer_sequence<T, S...>, F&& f) {
	using unpack_t = int[];
	(void)unpack_t{(static_cast<void>(f(std::integral_constant<T, S>{})), 0)..., 0};
}
template <typename Class, typename T>
struct PropertyImpl
{
        constexpr PropertyImpl(T Class::*aMember, const char* aName) : member{aMember}, name{aName} {}

        using Type = T;

        T Class::*member;
        const char* name;
};

template <typename Class, typename T>
constexpr auto property(T Class::*member, const char* name)
{
    return PropertyImpl<Class, T>{member, name};
};
class JsonFunction
{
    public:
        template <typename T>
        static Json::Value toJson(const T& object)
        {
            Json::Value data;

            // We first get the number of properties
            constexpr auto nbProperties = std::tuple_size<decltype(T::properties())>::value;

            // We iterate on the index sequence of size `nbProperties`
            for_sequence(std::make_index_sequence<nbProperties>{},
                         [&](auto i)
                         {
                             // get the property
                             constexpr auto property = std::get<i>(T::properties());

                             // set the value to the member
                             data[property.name] = object.*(property.member);
                         });

            return data;
        }
        template <typename T>
        static T fromJson(const Json::Value& data)
        {
            T object;

            // We first get the number of properties
            constexpr auto nbProperties = std::tuple_size<decltype(T::properties())>::value;

            // We iterate on the index sequence of size `nbProperties`
            for_sequence(std::make_index_sequence<nbProperties>{},
                         [&](auto i)
                         {
                             // get the property
                             constexpr auto property = std::get<i>(T::properties());

                             // get the type of the property
                             using Type = typename decltype(property)::Type;

                             // set the value to the member
                             // you can also replace `asAny` by `fromJson` to recursively serialize
                             object.*(property.member) = Json::asAny<Type>(data[property.name]);
                            //  object.*(property.member) = JsonFunction::fromJson<Type>(data[property.name]);
                         });

            return object;
        }
};
class Dog
{
        // template <typename Class, typename T>
        // friend struct PropertyImpl;

        friend class JsonFunction;

        std::string barkType;
        std::string color;
        int weight = 0;
        vEngine::Core::float4 newWeight;

        bool operator==(const Dog& rhs) const 
        {
            return std::tie(barkType, color, weight) == std::tie(rhs.barkType, rhs.color, rhs.weight);
        }

        constexpr static auto properties()
        {
            return std::make_tuple(
                property(&Dog::newWeight, "newWeight"), 
                property(&Dog::barkType, "barkType"), 
                property(&Dog::color, "color"), 
                property(&Dog::weight, "weight"));
        };
};
#endif /* _VENGINE_CORE_SCENE_HPP */
