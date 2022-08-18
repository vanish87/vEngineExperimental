
/// \file scene.cpp
/// \brief source file for Scene
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/scene.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// #include <external/lodepng.h>
// #include <external/tga.h>

#include <vengine/core/game_object_factory.hpp>
#include <vengine/animation/bone.hpp>
#include <vengine/animation/bone_component.hpp>
#include <vengine/animation/joint.hpp>
#include <vengine/animation/joint_component.hpp>
#include <vengine/animation/animation_clip.hpp>
#include <vengine/animation/animator_component.hpp>
#include <vengine/core/camera_component.hpp>
#include <vengine/rendering/material.hpp>
#include <vengine/core/mesh.hpp>
#include <vengine/core/mesh_renderer_component.hpp>
#include <vengine/core/resource_loader.hpp>
#include <vengine/core/transform_component.hpp>

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
            CHECK_ASSERT(this->meshes_.find(id) == this->meshes_.end());

            this->meshes_[id] = mesh;
        }

        void Scene::SetTexture(const std::string path, const TextureSharedPtr texture)
        {
            CHECK_ASSERT(!this->HasTexture(path));
            this->textures_[path] = texture;
        }
        bool Scene::HasTexture(const std::string path)
        {
            return this->textures_.find(path) != this->textures_.end();
        }
        TextureSharedPtr Scene::GetTexture(const std::string path)
        {
            CHECK_ASSERT(this->HasTexture(path));
            return this->textures_[path];
        }
        bool Scene::Load(const ResourceDescriptorSharedPtr descriptor)
        {
            // UNUSED_PARAMETER(descriptor);
            auto j = ParseJson(descriptor->file_path);
            auto go = this->shared_from_this();
            FromJson(j, go);

            // Assimp::Importer importer;
            // auto scene = importer.ReadFile(f, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);

            // this->HandleMeshes(scene);
            // this->HandleMaterials(scene);
            // // this->CreateTextures(scene);
            // this->HandleCameras(scene);
            // this->HandleAnimations(scene);

            // this->root_ = this->HandleNode(scene->mRootNode, scene);
            // this->root_->description_.name = "Assimp File: " + f;
            // // this->AddChild(root);
            // this->current_state_ = ResourceState::Loaded;
            return true;
        }
        ResourceState Scene::CurrentState()
        {
            return this->current_state_;
        }
        GameNodeSharedPtr Scene::HandleNode(const aiNode* node, const aiScene* scene)
        {
            auto gn = GameObjectFactory::Create<TransformComponent>();

            this->HandleBoneNode(node, gn);

            gn->description_.name = node->mName.data;
            // set transformation here
            auto transform = node->mTransformation;
            // parent->AddChild(game_node);
            std::string parentName = "None";
            if (node->mParent != nullptr) parentName = node->mParent->mName.data;
            PRINT("aiNode " << node->mName.data << " parent :" << parentName);

            for (uint32_t i = 0; i < node->mNumMeshes; ++i)
            {
                auto mesh_node = GameObjectFactory::Create<GameNode>();
                // scene_meshes_ contains same mesh data as they are in aiScene
                auto scene_mesh_id = node->mMeshes[i];

                auto ai_mesh = scene->mMeshes[scene_mesh_id];
                auto mesh = this->meshes_[scene_mesh_id];
                PRINT("aiNode " << node->mName.data << " with ai mesh name " << ai_mesh->mName.data);

                auto mesh_component = GameObjectFactory::Create<MeshComponent>();
                mesh_component->Reset(mesh);
                mesh_node->AttachComponent(mesh_component);

                auto mesh_renderer = GameObjectFactory::Create<MeshRendererComponent>();
                mesh_node->AttachComponent(mesh_renderer);

                auto mat = this->materials_[ai_mesh->mMaterialIndex];
                mesh_renderer->GO()->material_ = mat;

                gn->AddChild(mesh_node);
            }

            for (uint32_t c = 0; c < node->mNumChildren; ++c)
            {
                auto child = this->HandleNode(node->mChildren[c], scene);
                gn->AddChild(child);
            }

            return gn;
        }

        void Scene::HandleCameras(const aiScene* scene)
        {
            UNUSED_PARAMETER(scene);
            // ComponentDescription desc;
            // auto camera = GameNodeFactory::Create<CameraComponent>(desc);
            // camera->GO()->target = Context::GetInstance().GetRenderEngine().back_buffer_;

            // GameNodeDescription gndesc;
            // gndesc.type = GameNodeType::Transform;
            // auto gn = GameNodeFactory::Create(gndesc);
            // gn->AttachComponent(camera);
            // this->cameras_.emplace_back(gn);
            if (this->cameras_.size() == 0)
            {
                auto cam = GameObjectFactory::Default<Camera>();
                cam->target = Context::GetInstance().GetRenderEngine().back_buffer_;
                this->cameras_.emplace_back(cam);
            }

            PRINT("num of cameras: " << this->cameras_.size());
        };

        void Scene::HandleMaterials(const aiScene* scene)
        {
            UNUSED_PARAMETER(scene);
            // auto vs_file = ResourceLoader::GetInstance().GetFilePath("vs.hlsl");
            // auto ps_file = ResourceLoader::GetInstance().GetFilePath("ps.hlsl");
            // auto current_path = std::string();
            // for (uint32_t mid = 0; mid < scene->mNumMaterials; ++mid)
            // {
            //     auto ai_mat = scene->mMaterials[mid];
            //     auto mat = GameObjectFactory::Create<Material>();
            //     this->materials_.emplace_back(mat);
            //     aiString szPath;
            //     if (AI_SUCCESS == ai_mat->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), szPath))
            //     {
            //         auto texture_path = std::filesystem::path(ResourceLoader::GetInstance().GetFilePath(szPath.data));
            //         if (this->textures_.find(texture_path.string()) == this->textures_.end())
            //         {
            //             std::vector<byte> out;

            //             uint32_t width = 0;
            //             uint32_t height = 0;
            //             auto format = DataFormat::RGBA32;
            //             if (texture_path.extension() == ".png")
            //             {
            //                 auto error = lodepng::decode(out, width, height, texture_path.string());
            //                 CHECK_ASSERT(error == 0);
            //             }
            //             else if (texture_path.extension() == ".tga")
            //             {
            //                 FILE* f;
            //                 auto error = fopen_s(&f, texture_path.string().c_str(), "rb");
            //                 CHECK_ASSERT(error == 0);

            //                 tga::StdioFileInterface file(f);
            //                 tga::Decoder decoder(&file);
            //                 tga::Header header;
            //                 if (!decoder.readHeader(header)) CHECK_ASSERT(false);

            //                 tga::Image image;
            //                 image.bytesPerPixel = header.bytesPerPixel();
            //                 image.rowstride = header.width * header.bytesPerPixel();

            //                 out.resize(image.rowstride * header.height);
            //                 image.pixels = &out[0];

            //                 if (!decoder.readImage(header, image, nullptr)) CHECK_ASSERT(false);

            //                 width = header.width;
            //                 height = header.height;
            //             }
            //             else
            //             {
            //                 PRINT_AND_BREAK("texture file " << texture_path << " not supported");
            //             }

            //             TextureDescriptor tdesc;
            //             tdesc.width = width;
            //             tdesc.height = height;
            //             tdesc.depth = 1;
            //             tdesc.format = format;
            //             tdesc.dimension = TextureDimension::TD_2D;
            //             tdesc.type = GraphicsResourceType::TextureR;
            //             tdesc.usage = GraphicsResourceUsage::GPU_Read_Only;
            //             tdesc.resource.data = out.data();
            //             tdesc.resource.pitch = sizeof(byte) * GetByteSize(format) * width;
            //             tdesc.slot = GraphicsBufferSlot::Slot0;

            //             auto tex = Context::GetInstance().GetRenderEngine().Create(tdesc);
            //             this->textures_[texture_path.string()] = tex;
            //             PRINT(texture_path.relative_path().string() << " Loaded");
            //         }

            //         mat->textures_.push_back(this->textures_[texture_path.string()]);
            //     }
            // }
            // if (this->materials_.size() == 0)
            // {
            //     PRINT("no materials for scene, add a default material");
            //     auto mat = GameObjectFactory::Default<Material>();
            //     this->materials_.emplace_back(mat);
            // }
            // PRINT("num of materials: " << this->materials_.size());
        }

        void Scene::HandleMeshes(const aiScene* scene)
        {
            UNUSED_PARAMETER(scene);
            // for (uint32_t mid = 0; mid < scene->mNumMeshes; ++mid)
            // {
            //     // auto mesh = scene->mMeshes[mid];
            //     // auto mesh_go = GameObjectFactory::Create<Mesh>(mesh);
            //     // this->meshes_[mid] = mesh_go;
            // }

            PRINT("num of meshes: " << this->meshes_.size());
        }

        void Scene::HandleAnimations(const aiScene* scene)
        {
            for (uint32_t i = 0; i < scene->mNumAnimations; ++i)
            {
                auto animation = GameObjectFactory::Create<AnimationClip>();
                // each animation is an AnimationClip
                auto anim = scene->mAnimations[i];

                animation->description_.name = anim->mName.data;
                animation->Duration() = static_cast<float>(anim->mDuration);
                animation->TicksPerSecond() = static_cast<float>(anim->mTicksPerSecond);
                animation->TotalFrame() = Math::FloorToInt(anim->mDuration * anim->mTicksPerSecond);
                PRINT("handling " << animation->description_.name << " animation with " << animation->TotalFrame() << " frames")
                for (uint32_t c = 0; c < anim->mNumChannels; ++c)
                {
                    // Each channel defines node/bone it controls
                    // for example
                    // node->mNodeName = "Torso" contains key frames data for "Torso" Node/Bone in the scene
                    // mNodeName could be aiNode or aiBone
                    auto node = anim->mChannels[c];
                    PRINT("channel " << node->mNodeName.data << " has " << node->mNumPositionKeys << " Key values");

                    auto joint = GameObjectFactory::Create<Joint>();
                    joint->description_.name = node->mNodeName.data;

                    uint32_t k = 0;
                    for (k = 0; k < node->mNumPositionKeys; ++k)
                    {
                        auto pos = node->mPositionKeys[k];
                        joint->position_keys_.emplace_back((float)pos.mTime, float3(pos.mValue.x, pos.mValue.y, pos.mValue.z));
                    }
                    for (k = 0; k < node->mNumRotationKeys; ++k)
                    {
                        auto rotation = node->mRotationKeys[k];
                        joint->rotation_keys_.emplace_back((float)rotation.mTime, quaternion(rotation.mValue.w, rotation.mValue.x, rotation.mValue.y, rotation.mValue.z));
                    }
                    for (k = 0; k < node->mNumScalingKeys; ++k)
                    {
                        auto scale = node->mScalingKeys[k];
                        joint->scale_keys_.emplace_back((float)scale.mTime, float3(scale.mValue.x, scale.mValue.y, scale.mValue.z));
                    }

                    // TODO: use unordered_map for fast access
                    animation->AddJoint(joint->description_.name, joint);
                }

                this->animation_clips_.push_back(animation);
            }
        }
        void Scene::HandleBoneNode(const aiNode* node, const GameNodeSharedPtr game_node)
        {
            if (node == nullptr) return;

            auto bone_name = node->mName.data;
            for (const auto& m : this->meshes_)
            {
                if (m.second->bone_data_.find(bone_name) != m.second->bone_data_.end())
                {
                    // TODO Add init/bind pose pos/rotation/scale to bone_comp
                    auto bone_comp = m.second->bone_data_[bone_name];
                    game_node->AttachComponent(bone_comp);
                }
            }
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

    }  // namespace Core
}  // namespace vEngine