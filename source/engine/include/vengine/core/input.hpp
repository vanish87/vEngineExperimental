/// \file example_class.hpp
/// \brief Head file for class dll.
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_INPUT_HPP
#define _VENGINE_CORE_INPUT_HPP

#pragma once

/// A brief namespace description.
namespace vEngine
{
    /// A brief namespace description.
    namespace Core
    {
        enum Keyboard
        {
            None = 0,

            // Alphabetic keys (using ASCII values for simplicity)
            A = 65,
            B,
            C,
            D,
            E,
            F,
            G,
            H,
            I,
            J,
            K,
            L,
            M,
            N,
            O,
            P,
            Q,
            R,
            S,
            T,
            U,
            V,
            W,
            X,
            Y,
            Z,

            // Numeric keys (above the alphabetic keys)
            Num0 = 48,
            Num1,
            Num2,
            Num3,
            Num4,
            Num5,
            Num6,
            Num7,
            Num8,
            Num9,

            // Functional keys
            F1 = 112,
            F2,
            F3,
            F4,
            F5,
            F6,
            F7,
            F8,
            F9,
            F10,
            F11,
            F12,

            // Control keys
            Escape = 27,
            Enter = 13,
            Space = 32

        };
        enum Mouse
        {
            Left,    // Left mouse button
            Right,   // Right mouse button
            Middle,  // Middle mouse button (usually the scroll wheel button)
            X1,      // Extra button 1 (if present)
            X2       // Extra button 2 (if present)
        };
        enum Joystick
        {

        };
        enum Touch
        {

        };
        enum Sensor
        {

        };
        /// \brief A brief class description.
        ///
        /// To map input to different device
        /// and also class InputDevice etc.
        class InputEngine
        {
            public:
                /// \brief brief constructor description.
                InputEngine(){};

                /// class variable description
                int public_variable_;

            public:
                /// \brief A brief function description.
                ///
                /// \param p1 Description for p1.
                /// \param p2 Description for p2.
                /// \return Description for return value.
                // int GetVariable(int p1, float p2){};
        };
    }  // namespace Core

}  // namespace vEngine

#endif /* _VENGINE_CORE_INPUT_HPP */
