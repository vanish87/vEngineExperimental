/// \file bone_component.cpp
/// \brief source file for Bone Component
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/animation/bone_component.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Animation
    {

        using namespace Core;
        /// constructor detailed defintion,
        /// should be 2 lines
        BoneComponent::BoneComponent(const GameObjectType type) : Component(type) {}
        BoneComponent::~BoneComponent() {}
        // void BoneComponent::Update()
        //         {
        //             //Just Get transform and set to it's bone game object
        //             //so that mesh renderer can get this transform to render mesh

        //             //get scene node transform form it's Transform component
        //             //nodeTransform = this->Owner()->Transform(); -> this transform will be update by animator with calculated TRS from AnimationClip
        //             //set final matrix =  nodeTransform
        //         }

        /// A detailed function description, it
        /// should be 2 lines at least.
        int BoneComponent::GetVariable(int p1, float p2)
        {
            UNUSED_PARAMETER(p1);
            UNUSED_PARAMETER(p2);
            return 1;
        }

    }  // namespace Animation
}  // namespace vEngine