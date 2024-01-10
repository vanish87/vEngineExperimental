/// \file component.hpp
/// \brief Head file for Game Component
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_COMPONENT_HPP
#define _VENGINE_CORE_COMPONENT_HPP

#pragma once
#include <memory>

#include <engine.hpp>
#include <vengine/core/icomponent.hpp>
#include <vengine/core/game_node.hpp>
#include <vengine/core/game_object_factory.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        /// \brief Component model
        ///
        /// Unity-like Component model attached
        /// as game node in the scene
        template <typename T>
        class Component : public GameNode, public IComponent
        {
                static_assert(std::is_base_of<GameObject, T>::value, "T must derived from GameObject");
                static_assert(std::is_same<Component, T>::value == false, "T should not be Component");

            public:
                constexpr static auto properties()
                {
                    return std::tuple_cat(
                        GameNode::properties(), 
                        std::make_tuple(
                            property("enabled", &Component::enabled_), 
                            property("game_object", &Component::game_object_)
                        )
                    );
                }

            public:
                /// \brief brief constructor description.
                Component(const std::shared_ptr<T> go = GameObjectFactory::Default<T>()) : enabled_{false}, game_object_{go} {};
                virtual ~Component(){};

                virtual void OnInit() override
                {
                    // VE_INFO("Created "<< typeid(T).name() << " from component");
                    // this->descriptor_.name = std::string("Component ") + typeid(T).name();
                    // this->game_object_ = T::Default();
                    // this->game_object_ = std::make_shared<T>();
                }
                virtual bool Enabled() const override
                {
                    return this->enabled_;
                }
                virtual void SetEnable(const bool enable) override
                {
                    if (enable && !this->enabled_) this->OnEnable();
                    if (!enable && this->enabled_) this->OnDisable();
                    this->enabled_ = enable;
                }

            public:
                std::shared_ptr<T> GO()
                {
                    VE_ASSERT_PTR_NOT_NULL(this->game_object_);

                    return this->game_object_;
                }


            private:
                bool enabled_;
                std::shared_ptr<T> game_object_;

            public:
                virtual GameNodeSharedPtr Owner() override
                {
                    return this->Parent().lock();
                }
        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_COMPONENT_HPP */
