
/// \file animator_component.cpp
/// \brief source file for Animator Component
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/animation/animator_component.hpp>
#include <vengine/core/constants.hpp>
#include <vengine/core/transform_component.hpp>
#include <vengine/animation/bone_component.hpp>
#include <vengine/animation/joint.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Animation
    {

        /// constructor detailed defintion,
        /// should be 2 lines
        AnimatorComponent::AnimatorComponent()
        {
            // timer = 0;
        }
        AnimatorComponent::~AnimatorComponent() {}

        void AnimatorComponent::SetAnimationRoot(const Core::GameNodeSharedPtr root)
        {
            this->animation_root_ = root;
        }
        void AnimatorComponent::OnInit() {}

        void AnimatorComponent::OnUpdate()
        {
            // 1. Search same level to find skeleton/or skeleton already set
            // 2. Update Animator to Lerp Animation Clips
            // 3. Animator component will update current time TRS for all Bone Node

            Core::Component<Animator>::OnUpdate();
            auto animator = this->GO();
            animator->UpdateLerp(TIME_PER_UPDATE);

            // timer += TIME_PER_UPDATE;
            // int fid = Math::FloorToInt(timer);
            // auto fid = 0;

            // auto joints = animator->GetAnimatedJoints();
            // if (animator->current_clip_ == nullptr) animator->current_clip_ = animator->animations_[0];

            auto joints = animator->GetAnimatedJoints();

            this->animation_root_->TraverseAllChildren<BoneComponent>(
                [&](BoneComponentSharedPtr node)
                {
                    // node->UpdateLocal(parent);
                    // node->OnUpdate();

                    // set bone's Transform to animated TRS
                    auto transform = node->Owner()->FirstOf<Core::TransformComponent>();
                    CHECK_ASSERT(joints.find(node->description_.name) != joints.end());
                    
                    JointSharedPtr j = joints[node->description_.name];
                    // if(transform == nullptr || j == nullptr) return true;
                    // auto j = joints[0];

                    // auto ps = j->position_keys_.size();
                    // auto rs = j->rotation_keys_.size();
                    // auto ss = j->scale_keys_.size();

                    transform->GO()->Translate() = j->position_keys_[0].value;
                    transform->GO()->Rotation() = j->rotation_keys_[0].value;
                    transform->GO()->Scale() = j->scale_keys_[0].value;

                    // transform->GO()->Translate() = j->position_keys_[fid%ps].value;
                    // transform->GO()->Rotation() = j->rotation_keys_[fid%rs].value;
                    // transform->GO()->Scale() = j->scale_keys_[fid%ss].value;
                    // gn->Transform()->Scale() = Core::float3(0.5f, 0.5f, 0.5f);

                    // auto pos = node->game_object_->Translate();
                    // PRINT(pos.x() << " " << pos.y());
                    // PRINT(node->name_);
                    return true;
                });
        }

        /// A detailed function description, it
        /// should be 2 lines at least.
        int AnimatorComponent::GetVariable(int p1, float p2)
        {
            UNUSED_PARAMETER(p1);
            UNUSED_PARAMETER(p2);
            return 1;
        }

    }  // namespace Animation
}  // namespace vEngine