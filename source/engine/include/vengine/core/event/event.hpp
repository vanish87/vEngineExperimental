/// \file example_class.hpp
/// \brief Head file for class dll.
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _CORE_EVENT_EVENT_HPP
#define _CORE_EVENT_EVENT_HPP

#pragma once

#include <vengine/core/game_object.hpp>
#include <vengine/core/vector.hpp>
#include <vengine/core/input.hpp>
#include <vengine/data/from_to_string.hpp>
#include <string>

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        //temperal tpye from Hazel
        enum class EventType
        {
            None = 0,
            WindowClose,
            WindowResize,
            WindowFocus,
            WindowLostFocus,
            WindowMoved,
            AppTick,
            AppUpdate,
            AppRender,
            KeyPressed,
            KeyReleased,
            KeyTyped,
            MouseButtonPressed,
            MouseButtonReleased,
            MouseMoved,
            MouseScrolled
        };
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        Interface VENGINE_API IEvent
        {
        public:
            /// \brief A brief function description.
            ///
            /// \return Description for return value.
            virtual std::string ToString() const = 0;
        };
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class VENGINE_API WindowEvent : public GameObject, public IEvent
        {
            public:
                /// \brief brief constructor description.
                WindowEvent() : GameObject() {}

            public:
                /// \brief A brief function description.
                ///
                /// \return Description for return value.
                virtual std::string ToString() const override
                {
                    return "WindowEvent";
                };
        };
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class VENGINE_API MouseMoveEvent : public GameObject, public IEvent
        {
            public:
                /// \brief brief constructor description.
                MouseMoveEvent(float x, float y) : GameObject(), pos(x, y) {}

                float2 pos;

            public:
                /// \brief A brief function description.
                ///
                /// \param p1 Description for p1.
                /// \param p2 Description for p2.
                /// \return Description for return value.
                virtual std::string ToString() const override
                {
                    return "Event" + std::to_string(pos.x()) + " " + std::to_string(pos.y());
                };
        };
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class VENGINE_API MouseButtonEvent : public GameObject, public IEvent
        {
            public:
                /// \brief brief constructor description.
                MouseButtonEvent() : GameObject() {}

            public:
                /// \brief A brief function description.
                ///
                /// \param p1 Description for p1.
                /// \param p2 Description for p2.
                /// \return Description for return value.
                virtual std::string ToString() const override
                {
                    return "Event";
                };
        };
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class VENGINE_API KeyEvent : public GameObject, public IEvent
        {
            public:
                /// \brief brief constructor description.
                KeyEvent(const Keyboard key_code) : GameObject(), key_code_(key_code) {}

            public:
                /// \brief A brief function description.
                ///
                /// \param p1 Description for p1.
                /// \param p2 Description for p2.
                /// \return Description for return value.
                virtual std::string ToString() const override
                {
                    std::string code;
                    ::vEngine::Core::ToString(this->key_code_, code);
                    return "Key Event" + code;
                };

            private:
                Keyboard key_code_;
        };
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class VENGINE_API KeyPressedEvent : public KeyEvent
        {
            public:
                /// \brief brief constructor description.
                KeyPressedEvent(const Keyboard key_code) : KeyEvent(key_code) {}

            public:
                /// \brief A brief function description.
                ///
                /// \param p1 Description for p1.
                /// \param p2 Description for p2.
                /// \return Description for return value.
                virtual std::string ToString() const override
                {
                    return KeyEvent::ToString() + " Pressed";
                };
        };

        Interface VENGINE_API IEventDispatcher
        {
        public:
            virtual void AddListenner(const IEventListenerSharedPtr listener) = 0;
            virtual void RemoveListener(const IEventListenerSharedPtr listener) = 0;
            virtual void Dispath(const IEvent& event) = 0;
        };
        Interface VENGINE_API IEventListener
        {
        public:
            virtual bool OnEvent(const IEvent& event) = 0;
        };

    }  // namespace Core

}  // namespace vEngine

#endif /* _CORE_EVENT_EVENT_HPP */
