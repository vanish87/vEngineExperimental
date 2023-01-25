/// \file bone.hpp
/// \brief Head file for Bone in mesh
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_ANIMATION_BONE_HPP
#define _VENGINE_ANIMATION_BONE_HPP

#pragma once

#include <engine.hpp>
#include <vengine/core/matrix.hpp>
#include <vengine/core/game_object.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Animation
    {
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class VENGINE_API Bone : public Core::GameObject
        {
            public:
                static BoneSharedPtr Default()
                {
                    const static auto bone = Core::GameObjectFactory::Create<Core::GameObjectType::Bone, Bone>();
                    return bone;
                }
                constexpr static auto properties()
                {
                    return std::tuple_cat(
                        GameObject::properties(),
                        std::make_tuple(
                            property("id", &Bone::id_),
                            property("inverse_bind_pose_matrix", &Bone::inverse_bind_pose_matrix_)
                        )
                    );
                }
            public:
                /// \brief brief constructor description.
                Bone(const Core::GameObjectType type = Core::GameObjectType::Bone);

                /// class variable description
                int id_;
				// std::vector<VertexWeight> weights;
				Core::float4x4 inverse_bind_pose_matrix_;
            public:
                /// \brief A brief function description.
                ///
                /// \param p1 Description for p1.
                /// \param p2 Description for p2.
                /// \return Description for return value.
                int GetVariable(int p1, float p2);
        };
    }  // namespace Animation

}  // namespace vEngine

#endif /* _VENGINE_ANIMATION_BONE_HPP */
