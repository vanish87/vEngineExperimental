#ifndef _ASSIMP_TO_JSON_SOURCE_BASE_CLASS_HPP
#define _ASSIMP_TO_JSON_SOURCE_BASE_CLASS_HPP

#include <vector>
#include <engine.hpp>
#include <predeclear.hpp>

#include <vengine/data/meta.hpp>
#include <vengine/core/game_object.hpp>
#include <vengine/core/game_object_factory.hpp>
#include <class_bar.hpp>

namespace vEngine
{
    namespace Core
    {
        class ClassFoo : public GameObject
        {
            public:
                constexpr static auto properties()
                {
                    return std::tuple_cat(
                        GameObject::properties(), 
                        std::make_tuple(
                            property("pos", &ClassFoo::pos),
                            property("content", &ClassFoo::content),
                            property("my_vector", &ClassFoo::vector),
                            type<ClassFoo>()
                            )
                    );
                }

            public:
                ClassFoo()
                {
                    this->vector.push_back(GameObjectFactory::Create<ClassBar>());
                    this->vector.push_back(GameObjectFactory::Create<ClassBar>());
                    this->vector.push_back(GameObjectFactory::Create<ClassBar>());
                }
                virtual ~ClassFoo() {}

            private:
                float4 pos;
                std::string content = "MyContent";
                std::vector<std::shared_ptr<ClassBar>> vector;
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _ASSIMP_TO_JSON_SOURCE_BASE_CLASS_HPP */
