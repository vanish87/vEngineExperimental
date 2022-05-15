/// \file transform.hpp
/// \brief Head file for Transform
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_TRANSFORM_HPP
#define _VENGINE_CORE_TRANSFORM_HPP

#pragma once

#include <engine.hpp>
#include <vengine/core/matrix.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class Transform
        {
            public:
                /// \brief brief constructor description.
                Transform()
                {
                    // local_ = float4x4::IdentityMat();
                    local_to_world_ = float4x4::IdentityMat();
                    local_rotation_ = float4x4::IdentityMat();
                    local_scale_ = float3::One();
                    local_pos_ = float3::Zero();
                };

                /// class variable description
                // int public_variable_;

                float3 local_pos_;
                float4x4 local_rotation_;
                float3 local_scale_;

                // float4x4 local_;

                const float4x4 GetLocal()
                {
                    float4x4 t;
                    float4x4 r = float4x4::IdentityMat();
                    float4x4 s;
                    Math::Translate(t, this->local_pos_);
                    // Math::RotationAxis(r, this->local_rotation_);
                    Math::Scale(s, this->local_scale_);
                    // return t * r * s;
                    return s * r * t;
                }

                float4x4 local_to_world_;

            public:
                /// \brief A brief function description.
                ///
                /// \param p1 Description for p1.
                /// \param p2 Description for p2.
                /// \return Description for return value.
                // int GetVariable(int p1, float p2);
        };
    }  // namespace Core

}  // namespace vEngine

#endif /* _VENGINE_CORE_TRANSFORM_HPP */
