
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
#include <vengine/core/transform.hpp>
#include <vengine/core/transform_node.hpp>
#include <vengine/animation/joint_component.hpp>

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
                case GameNodeType::Transform:
                {
                    ret = std::make_shared<TransformNode>();
                    ComponentDescription cdesc;
                    ret->AttachComponent(Create<TransformComponent>(cdesc));
                }
                break;
                case GameNodeType::Skeleton:
                {
                    ret = std::make_shared<Skeleton>();
                    ComponentDescription cdesc;
                    ret->AttachComponent(Create<TransformComponent>(cdesc));
                }
                break;
                case GameNodeType::Joint:
                {
                    ret = std::make_shared<GameNode>();
                    ComponentDescription cdesc;
                    ret->AttachComponent(Create<TransformComponent>(cdesc));
                    ret->AttachComponent(Create<JointComponent>(cdesc));
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