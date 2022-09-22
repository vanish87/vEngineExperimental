#ifndef _VENGINE_DATA_CLASS_BAR_HPP
#define _VENGINE_DATA_CLASS_BAR_HPP

#include <engine.hpp>

#include <vengine/data/meta.hpp>
#include <vengine/core/game_object.hpp>
#include <vengine/core/vector.hpp>

namespace vEngine
{
    namespace Core
    {
        class ClassBar : public GameObject
        {
            public:
                constexpr static auto properties()
                {
                    return std::tuple_cat(
                        GameObject::properties(), 
                        std::make_tuple(
                            property("pos", &ClassBar::pos),
                            property("content", &ClassBar::content)
                            )
                    );
                }

            public:
                ClassBar()
                {
                    // this->vector.push_back(new )
                }
                virtual ~ClassBar() {}

            private:
                float4 pos;
                std::string content = "BarContent";
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_DATA_CLASS_BAR_HPP */
