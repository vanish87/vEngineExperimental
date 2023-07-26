/// \file light.hpp
/// \brief Head file for Light
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_LIGHT_HPP
#define _VENGINE_CORE_LIGHT_HPP

#include <vengine/core/game_object.hpp>
#include <vengine/core/vector.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class VENGINE_API Light : public GameObject
        {
            public:
                constexpr static auto properties()
                {
                    return std::tuple_cat(
                        GameObject::properties(),
                        std::make_tuple(
                            property("fall_off", &Light::fall_off_)
                        )
                    );
                }
                static LightSharedPtr Default();
            public:
                /// \brief brief constructor description.
                Light();

                protected:
                float4 fall_off_;

				//color
				//intensity
				//etc.


        };
    }  // namespace Core
}  // namespace vEngine

#endif /* _VENGINE_CORE_LIGHT_HPP */
