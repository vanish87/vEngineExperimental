
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
#include <vengine/core/game_object_factory.hpp>
#include <vengine/core/transform_component.hpp>
#include <vengine/core/asset_component.hpp>
#include <vengine/core/camera_component.hpp>
#include <vengine/animation/bone_component.hpp>
#include <vengine/animation/bone_component.hpp>
#include <vengine/animation/skeleton_component.hpp>
#include <vengine/animation/animator_component.hpp>
#include <vengine/core/mesh_component.hpp>
#include <vengine/core/mesh_renderer_component.hpp>
#include <vengine/core/material.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {
        using namespace Animation;
        using namespace Rendering;

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
                case GameNodeType::Camera:
                {
                    ret = std::make_shared<GameNode>();
                    ComponentDescription cdesc;
                    ret->AttachComponent(Create<TransformComponent>(cdesc));
                    ret->AttachComponent(Create<CameraComponent>(cdesc));
                }
                break;
                case GameNodeType::DefaultCube:
                {
                    ret = std::make_shared<GameNode>();
                    ComponentDescription cdesc;
                    ret->AttachComponent(Create<TransformComponent>(cdesc));

                    auto mesh = Create<MeshComponent>(cdesc);
                    mesh->Reset(GameObjectFactory::Default<Mesh>(MeshPrimitive::Cube));
                    ret->AttachComponent(mesh);

                    auto renderer = Create<MeshRendererComponent>(cdesc);
                    renderer->GO()->material_ = GameObjectFactory::Default<Material>();
                    ret->AttachComponent(renderer);
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