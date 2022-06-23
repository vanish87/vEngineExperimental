
/// \file game_node_factory.cpp
/// \brief source file for Game Node Factory
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/animation/skeleton.hpp>
#include <vengine/core/game_node_factory.hpp>
#include <vengine/core/transform_component.hpp>
#include <vengine/core/asset_component.hpp>
#include <vengine/animation/bone_component.hpp>
#include <vengine/animation/bone_component.hpp>
#include <vengine/animation/skeleton_component.hpp>
#include <vengine/animation/animator_component.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {
        using namespace Animation;

        /// A detailed function description, it
        /// should be 2 lines at least.
        // TransformNodeSharedPtr GameNodeFactory::Create()
        // {
        //     ComponentDescription desc;
        //     auto gn = std::make_shared<TransformNode>();
        //     gn->transform_ = Create<TransformComponent>(desc);
        //     gn->AttachComponent(gn->transform_);
        //     return gn;
        // }
        GameNodeSharedPtr GameNodeFactory::Create(const GameNodeDescription& desc)
        {
            GameNodeSharedPtr ret = nullptr;
            switch (desc.type)
            {
                case GameNodeType::Asset:
                {
                    ret = std::make_shared<GameNode>();
                    ComponentDescription cdesc;
                    ret->AttachComponent(Create<AssetComponent>(cdesc));
                }
                break;
                case GameNodeType::Transform:
                {
                    ret = std::make_shared<GameNode>();
                    ComponentDescription cdesc;
                    ret->AttachComponent(Create<TransformComponent>(cdesc));
                }
                break;
                case GameNodeType::Skeleton:
                {
                    ret = std::make_shared<GameNode>();
                    ComponentDescription cdesc;
                    ret->AttachComponent(Create<TransformComponent>(cdesc));
                    ret->AttachComponent(Create<SkeletonComponent>(cdesc));
                }
                break;
                case GameNodeType::Bone:
                {
                    ret = std::make_shared<GameNode>();
                    ComponentDescription cdesc;
                    ret->AttachComponent(Create<TransformComponent>(cdesc));
                    ret->AttachComponent(Create<BoneComponent>(cdesc));
                }
                break;
                case GameNodeType::Animator:
                {
                    ret = std::make_shared<GameNode>();
                    ComponentDescription cdesc;
                    ret->AttachComponent(Create<AnimatorComponent>(cdesc));
                    // ret->AttachComponent(Create<BoneComponent>(cdesc));
                }
                break;


                default:
                    break;
            }
            if (ret == nullptr)
            {
                PRINT("Raw GameNode Created");
                ret = std::make_shared<GameNode>();
            }

            return ret;
        }

    }  // namespace Core
}  // namespace vEngine