
/// \file scene.cpp
/// \brief source file for Scene
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx
#include <vengine/core/scene.hpp>

#include <external/lodepng.h>
#include <external/tga.h>

#include <vengine/core/game_node_factory.hpp>
#include <vengine/core/game_object_factory.hpp>
#include <vengine/animation/bone.hpp>
#include <vengine/animation/bone_component.hpp>
#include <vengine/animation/joint.hpp>
#include <vengine/animation/joint_component.hpp>
#include <vengine/animation/skeleton.hpp>
#include <vengine/animation/skeleton_component.hpp>
#include <vengine/animation/animation_clip.hpp>
#include <vengine/animation/animator_component.hpp>
#include <vengine/core/camera_component.hpp>
#include <vengine/core/material.hpp>
#include <vengine/core/mesh.hpp>
#include <vengine/core/mesh_renderer_component.hpp>
#include <vengine/core/resource_loader.hpp>
#include <vengine/core/transform_component.hpp>
#include <vengine/core/asset_component.hpp>

// #include <vengine/rendering/render_engine.hpp>
/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {
        /// constructor detailed defintion,
        /// should be 2 lines
        Scene::Scene() : GameNode()
        {
            // this->file_path_ = file_path;
            // this->name_ = file_path;
            // this->state_ = ResourceState::Unknown;
            // this->root_ = std::make_shared<GameNode>();
        }
        void Scene::LoadFile(const std::string file)
        {
            PRINT("Loading " << file);

            GameNodeDescription gndesc;
            gndesc.type = GameNodeType::Asset;
            auto gn = GameNodeFactory::Create(gndesc);
            auto asset = gn->FirstOf<AssetComponent>();
            ResourceDescriptor rdesc;
            rdesc.file_path = file;
            asset->GO()->Load(rdesc);

            gn->AddChild(asset->GO()->root_);

            this->AddChild(gn);
        }
        void Scene::ActiveScene()
        {
            //find first available camera as main camera;
            //link each animation to its mesh with newly created animator node
            auto asset = this->FirstOf<AssetComponent>(1);

            // asset->GO()->root_->FirstOf<TransformComponent>()->GO()->Translate() = float3(0, 0, 5);
            // auto s = 0.01f;
            // asset->GO()->root_->FirstOf<TransformComponent>()->GO()->Scale() = float3(s,s,s);

            auto main_camera = asset->GO()->cameras_[0];
            GameNodeDescription gndesc;
            gndesc.type = GameNodeType::Camera;
            auto camera_gn = GameNodeFactory::Create(gndesc);
            camera_gn->FirstOf<CameraComponent>()->Reset(main_camera);
            camera_gn->FirstOf<TransformComponent>()->GO()->Translate() = float3(0,-20,120);
            this->AddChild(camera_gn);

            gndesc.type = GameNodeType::Animator;
            auto animator_gn = GameNodeFactory::Create(gndesc);
            auto animator_comp = animator_gn->FirstOf<Animation::AnimatorComponent>();
            animator_comp->GO()->Setup(asset->GO()->animation_clips_);
            animator_comp->animation_root_ = asset->GO()->root_;
            this->AddChild(animator_gn);

            this->TraverseAllChildren<IComponent>(
                [&](IComponentSharedPtr comp)
                {
                    comp->SetEnable(true);
                    return true;
                });

        }

        float timer = 0;

        void Scene::Update()
        {
            timer += 0.001f;
            auto asset = this->FirstOf<AssetComponent>(1);
            auto rot90 = Math::RotateAngleAxis(Math::PI * 0.5f, float3(0,0,1));
            auto rotanim = Math::RotateAngleAxis(timer, float3(1,0,0));
            asset->GO()->root_->FirstOf<TransformComponent>()->GO()->Rotation() = rot90 * rotanim;
            this->TraverseAllChildren<Animation::AnimatorComponent>(
                [&](Animation::AnimatorComponentSharedPtr node)
                {
                    node->OnUpdate();
                    return true;
                });

            this->TraverseAllChildren<TransformComponent>(
                [&](TransformComponentSharedPtr node)
                {
                    node->OnUpdate();
                    return true;
                });

            this->TraverseAllChildren<CameraComponent>(
                [&](CameraComponentSharedPtr c)
                {
                    c->OnBeginCamera();

                    auto cam = c->GO();
                    auto frameBuffer = cam->target;
                    auto& re = Context::GetInstance().GetRenderEngine();
                    re.Bind(frameBuffer);
                    re.OnBeginFrame();
                    this->Flush();
                    re.OnEndFrame();
                    // render all game node
                    // PRINT("Camera");
                    return true;
                });
        }
        void Scene::Flush()
        {
            this->TraverseAllChildren<MeshRendererComponent>(
                [&](MeshRendererComponentSharedPtr n)
                {
                    n->OnUpdate();

                    n->OnBeginRender();
                    if (n->GO() != nullptr)
                    {
                        n->GO()->Render();
                    }
                    // Render other renderers(transparent, particle etc.) if possible
                    return true;
                });
        }
        void Scene::AddTestNode() {}
        void Scene::AddToSceneNode(const GameNodeSharedPtr new_node, const GameNodeSharedPtr game_node /*= nullptr*/)
        {
            // if (game_node == nullptr)
            // {
            //     this->AddChild(new_node);
            // }
            // else
            // {
            // this->Traverse<GameNode>(
            //     [&](GameNodeSharedPtr n)
            //     {
            //         if (n == game_node)
            //         {
            //             n->AddChild(new_node);
            //             return false;
            //         }
            //         return true;
            //     });
            // }
        }
        void Scene::Print()
        {
            this->TraverseAllChildren<GameNode>(
                [&](GameNodeSharedPtr gn)
                {
                    auto p = gn->Parent().lock();
                    auto pname = p != nullptr ? p->name_ : "None";
                    // auto name = gn->HasComponent<TransformComponent>()?"Transform":"Raw";
                    // auto cname = gn->HasComponent<CameraComponent>()?"Camera":"Raw";
                    // PRINT("Game Node " << name << " " << cname << " " << gn->name_ << " Parent " << pname);
                    auto comp = std::dynamic_pointer_cast<IComponent>(gn);
                    if (comp != nullptr) return true;

                    PRINT("Game Node " << gn->name_ << " Parent " << pname);
                    gn->ForEachChild<IComponent>(
                        [&](IComponentSharedPtr child)
                        {
                            auto cn = std::dynamic_pointer_cast<TransformComponent>(child);
                            if (cn == nullptr) return;
                            auto bone = std::dynamic_pointer_cast<Animation::BoneComponent>(child);
                            auto name = cn->name_;
                            if (bone != nullptr) name += " BoneComponent";

                            PRINT("Game Node " << gn->name_ << " Has " << name);

                            auto pos = cn->GO()->Translate();
                            PRINT(pos.x() << " " << pos.y() << " " << pos.z());
                            auto mat = cn->GO()->LocalToWorldTransform();
                            PRINT("Global " << mat[3][0] << " " << mat[3][1] << " " << mat[3][2]);
                            // PRINT(typeid(gn).name());
                            // return true;
                        });

                    return true;
                });
        }
    }  // namespace Core

}  // namespace vEngine