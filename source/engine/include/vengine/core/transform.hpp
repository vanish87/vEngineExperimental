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

#include <VENGINE_API.hpp>
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
        class VENGINE_API Transform final
        {
            public:
                /// \brief Constructor: use init list {} to initialize data
                Transform() noexcept
                {
                    this->local_translate_ = float3::Zero();
                    this->local_rotation_ = float4x4::IdentityMat();
                    this->local_scale_ = float3::One();
                    this->local_to_world_ = float4x4::IdentityMat();
                }

                /// \brief big five - 3: copy constructor
                ///
                /// copy constructor is called by \n
                ///  1. ClassA a = b; -> declear and assignment \n
                ///  2. Func(ClassA a) -> pass by value \n
                ///  3. return temp; -> return by value \n
                Transform(const Transform& other) noexcept
                {
                    this->local_translate_ = other.local_translate_;
                    this->local_rotation_ = other.local_rotation_;
                    this->local_scale_ = other.local_scale_;
                    this->local_to_world_ = other.local_to_world_;
                }

                /// \brief big five - 2: assignment operator
                ///
                /// with const formal paramter \n
                /// usage of constexpr: \n
                /// constexpr can not pass clang compiling => don't need constexpr as following \n
                /// constexpr Vector& operator=(const Vector& other) noexcept \n
                Transform& operator=(const Transform& other) noexcept
                {
                    // 1.check self assignment
                    if (this != &other)
                    {
                        this->local_translate_ = other.local_translate_;
                        this->local_rotation_ = other.local_rotation_;
                        this->local_scale_ = other.local_scale_;
                        this->local_to_world_ = other.local_to_world_;
                    }
                    return *this;
                }

                /// \brief big five - 1: virtual destructor
                ///
                /// to assure destructor of
                /// subclass called
                /// do not need for vector class
                // virtual ~Vector() noexcept {}

                /// \brief big five - 4: move constructor
                ///
                /// const is not needed: constexpr Vector(const Vector &&other) \n
                /// The move constructor: \n
                /// - Takes an r-value reference as a parameter. \n
                /// - Discards the object’s current state. \n
                /// - Transfers ownership of the r-value object into the receiver \n
                /// - Puts the r-value object into an 'empty' state. \n
                /// - subclass must explicitly std::move the base class \n
                Transform(Transform&& other) noexcept
                {
                    this->local_translate_ = std::move(other.local_translate_);
                    this->local_rotation_ = std::move(other.local_rotation_);
                    this->local_scale_ = std::move(other.local_scale_);
                    this->local_to_world_ = std::move(other.local_to_world_);
                }

                /// \brief big five - 5 : move operator
                ///
                /// move operator
                /// is used like unique_ptr
                Transform& operator=(const Transform&& other) noexcept
                {
                    // 1.check self assignment
                    if (this != &other)
                    {
                        // 2.allocate new object before-> to assure memory
                        // before delete existing one
                        this->local_translate_ = std::move(other.local_translate_);
                        this->local_rotation_ = std::move(other.local_rotation_);
                        this->local_scale_ = std::move(other.local_scale_);
                        this->local_to_world_ = std::move(other.local_to_world_);
                    }
                    return *this;
                }

                /// \brief init constructor
                ///
                /// use {} to init data, \n
                /// it will generate a compile error if
                /// vector is initd with more parameter than it has
                Transform(const float3& translate, const float4x4& rotation, const float3& scale) : local_translate_{translate}, local_rotation_{rotation}, local_scale_{scale} {}

                const float3& Translate() const
                {
                    return this->local_translate_;
                }
                const float4x4& Rotation() const
                {
                    return this->local_rotation_;
                }
                const float3& Scale() const
                {
                    return this->local_scale_;
                }

                float3& Translate() 
                {
                    return const_cast<float3&>(static_cast<const Transform*>(this)->Translate());
                }
                float4x4& Rotation()
                {
                    return const_cast<float4x4&>(static_cast<const Transform*>(this)->Rotation());
                }
                float3& Scale()
                {
                    return const_cast<float3&>(static_cast<const Transform*>(this)->Scale());
                }
                void UpdateLocalToWorld(const Transform& parent)
                {
                    this->local_to_world_ = this->LocalTransform() * parent.LocalToWorldTransform();
                }


            public:
                /// \brief static all 0 vector
                static const Transform& Identity()
                {
                    static const Transform transform;
                    return transform;
                }

                /// class variable description
                // int public_variable_;

                float4x4 LocalTransform() const
                {
                    float4x4 t;
                    float4x4 r = float4x4::IdentityMat();
                    float4x4 s;
                    Math::Translate(t, this->local_translate_);
                    // Math::RotationAxis(r, this->local_rotation_);
                    Math::Scale(s, this->local_scale_);
                    // return t * r * s;
                    return s * r * t;
                }
                float4x4 LocalToWorldTransform() const
                {
                    return this->local_to_world_;
                }

            private:
                float3 local_translate_;
                float4x4 local_rotation_;
                float3 local_scale_;

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
