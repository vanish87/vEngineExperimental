
/// \file scene.cpp
/// \brief source file for Scene
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/scene.hpp>

// #include <assimp/Importer.hpp>
// #include <assimp/scene.h>
// #include <assimp/postprocess.h>

// #include <external/lodepng.h>
// #include <external/tga.h>

#include <vengine/core/game_object_factory.hpp>
#include <vengine/core/camera_component.hpp>
#include <vengine/core/mesh.hpp>
#include <vengine/core/resource_manager.hpp>
#include <vengine/core/transform_component.hpp>
#include <vengine/core/light.hpp>
#include <vengine/core/light_component.hpp>
#include <vengine/animation/bone.hpp>
#include <vengine/animation/bone_component.hpp>
#include <vengine/animation/joint.hpp>
#include <vengine/animation/animation_clip.hpp>
#include <vengine/animation/animator_component.hpp>
#include <vengine/rendering/render_engine.hpp>
#include <vengine/rendering/material.hpp>
#include <vengine/rendering/mesh_renderer_component.hpp>

#include <vengine/data/json.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {
        using namespace Animation;
        using namespace Rendering;

        /// constructor detailed defintion,
        /// should be 2 lines
        Scene::Scene() {}
        Scene::~Scene() {}
        const CameraSharedPtr Scene::GetCamera(const uint32_t index) const
        {
            return this->cameras_[index];
        }
        const std::vector<AnimationClipSharedPtr> Scene::GetAnimations() const
        {
            return this->animation_clips_;
        }
        void Scene::AddMaterial(const MaterialSharedPtr material)
        {
            this->materials_.push_back(material);
        }
        void Scene::AddAnimation(const AnimationClipSharedPtr animation_clip)
        {
            this->animation_clips_.push_back(animation_clip);
        }
        void Scene::SetMesh(const int id, const MeshSharedPtr mesh)
        {
            VE_ASSERT(this->meshes_.find(id) == this->meshes_.end());

            this->meshes_[id] = mesh;
        }

        void Scene::SetTexture(const std::string name, const TextureSharedPtr texture)
        {
            VE_ASSERT(!this->HasTexture(name));
            this->textures_[name] = texture;
        }
        bool Scene::HasTexture(const std::string name)
        {
            return this->textures_.find(name) != this->textures_.end();
        }
        TextureSharedPtr Scene::GetTexture(const std::string name)
        {
            VE_ASSERT(this->HasTexture(name));
            return this->textures_[name];
        }

        /// A detailed function description, it
        /// should be 2 lines at least.
        int Scene::GetVariable(int p1, float p2)
        {
            UNUSED_PARAMETER(p1);
            UNUSED_PARAMETER(p2);
            return 1;
        }
        void Scene::Update()
        {
            // timer += 0.001f;
            // auto asset = this->FirstOf<AssetComponent>(1);
            // auto rot90 = Math::RotateAngleAxis(Math::PI * 0.5f, float3(0,0,1));
            // auto rotanim = Math::RotateAngleAxis(timer, float3(1,0,0));
            // asset->GO()->GetRoot()->FirstOf<TransformComponent>()->GO()->Rotation() = rot90 * rotanim;

            this->TraverseAllChildren<AnimatorComponent>(
                [&](AnimatorComponentSharedPtr node)
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

            auto& re = Context::GetInstance().GetRenderEngine();

            this->TraverseAllChildren<CameraComponent>(
                [&](CameraComponentSharedPtr c)
                {
                    c->OnBeginCamera();

                    auto cam = c->GO();
                    if (cam->target == nullptr) cam->target = Context::GetInstance().GetRenderEngine()->back_buffer_;
                    auto frameBuffer = cam->target;
                    re->Bind(frameBuffer);
                    re->OnBeginFrame();
                    this->Flush();
                    re->OnEndFrame();
                    return true;
                });

            //TODO it is resonable to seperate FrameBuffer to different
            //for example 3D 2D Overlay etc.

            re->SwapBuffer();
        }
        void Scene::Flush()
        {
            // TODO Sort by Material then foreach mat render mesh
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

    }  // namespace Core
}  // namespace vEngine