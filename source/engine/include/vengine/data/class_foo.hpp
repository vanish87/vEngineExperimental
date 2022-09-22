#ifndef _ASSIMP_TO_JSON_SOURCE_BASE_CLASS_HPP
#define _ASSIMP_TO_JSON_SOURCE_BASE_CLASS_HPP

#include <vector>
#include <engine.hpp>

#include <vengine/data/meta.hpp>
#include <vengine/core/game_object.hpp>
#include <vengine/core/game_object_factory.hpp>
#include <vengine/data/class_bar.hpp>

#include <vengine/core/matrix.hpp>

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
                            property("matrix", &ClassFoo::matrix),
                            property("content", &ClassFoo::content),
                            property("my_vector", &ClassFoo::vector),
                            property("my_path", &ClassFoo::file_path)
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

            public:
                float4 pos;
                float4x4 matrix;
                std::string content = "MyContent";
                std::vector<std::shared_ptr<ClassBar>> vector;
                std::filesystem::path file_path;
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _ASSIMP_TO_JSON_SOURCE_BASE_CLASS_HPP */
