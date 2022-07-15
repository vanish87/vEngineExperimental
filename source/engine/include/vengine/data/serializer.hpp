/// \file serializer.hpp
/// \brief Head file for Serializer
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_DATA_SERIALIZER_HPP
#define _VENGINE_DATA_SERIALIZER_HPP

#pragma once

#include <engine.hpp>
#include <vengine/core/game_object.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Data
    {
        Interface ISerializable
        {

        };

        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class Serializer : public Core::GameObject
        {
            public:
                /// \brief brief constructor description.
                Serializer();
                virtual ~Serializer();

                void Serialize(ISerializable data)
                {
                    // data.setvalue<int>("x", x):
                    UNUSED_PARAMETER(data);
                }
                void Deserialize(ISerializable data)
                {
                    // this->x = data.getvalue<int>("x", x):
                    UNUSED_PARAMETER(data);
                }

            public:
                /// \brief A brief function description.
                ///
                /// \param p1 Description for p1.
                /// \param p2 Description for p2.
                /// \return Description for return value.
                int GetVariable(int p1, float p2);
        };
    }  // namespace Data

}  // namespace vEngine

#endif /* _VENGINE_DATA_SERIALIZER_HPP */
