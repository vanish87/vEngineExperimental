
/// \file scene.cpp
/// \brief source file for Scene
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx
#include <external/lodepng.h>

#include <vengine/core/camera_component.hpp>
#include <vengine/core/game_node_factory.hpp>
#include <vengine/core/game_object_factory.hpp>
#include <vengine/core/material.hpp>
#include <vengine/core/mesh.hpp>
#include <vengine/core/mesh_renderer_component.hpp>
#include <vengine/core/resource_loader.hpp>
#include <vengine/core/scene.hpp>
#include <vengine/core/transform_component.hpp>

#include <vengine/animation/joint.hpp>
#include <vengine/animation/skeleton.hpp>

// #include <vengine/rendering/render_engine.hpp>
/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {
        /// constructor detailed defintion,
        /// should be 2 lines
        Scene::Scene(const std::string file_path) : GameNode()
        {
            this->file_path_ = file_path;
            this->name_ = file_path;
            this->state_ = ResourceState::Unknown;
            // this->root_ = std::make_shared<GameNode>();
        }

        ResourceState Scene::CurrentState()
        {
            return this->state_;
        }

        bool Scene::Load()
        {
            // this->AddTestNode();
            this->state_ = ResourceState::Loading;

            Assimp::Importer importer;
            auto scene = importer.ReadFile(this->file_path_, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
            this->CreateMeshes(scene);
            this->CreateMaterials(scene);
            this->CreateTextures(scene);
            this->CreateCameras(scene);
            this->CreateAnimations(scene);

            auto root = this->HandleNode(scene->mRootNode, scene);
            root->name_ = "Assimp Root";
            this->AddChild(root);

            // auto root = ComponentFactory::Create<TransformComponent>();
            // root->name_ = "SceneRoot";
            // this->AddChild(root);

            // auto trans = std::make_shared<TransformComponent>();
            // trans->game_object_->Translate() = float3(0, 0, 0);
            // this->AttachComponent(trans);

            // auto s = 1.5f;
            // auto s = 0.01f;
            auto root_transform = std::dynamic_pointer_cast<TransformNode>(root);
            // root_transform->Transform()->Scale() = float3(s, s, s);
            root_transform->Transform()->Translate() = float3(0.0f, -100, 100);
            // root_transform->Transform()->Translate() = float3(0.0f, 0, 1);

            this->TraverseAllChildren<IComponent>(
                [&](IComponentSharedPtr comp)
                {
                    comp->SetEnable(true);
                    return true;
                });

            this->state_ = ResourceState::Loaded;
            return true;
        }
        void Scene::CreateCameras(const aiScene* scene)
        {
            UNUSED_PARAMETER(scene);
            ComponentDescription desc;
            auto camera = GameNodeFactory::Create<CameraComponent>(desc);
            camera->GO()->target = Context::GetInstance().GetRenderEngine().back_buffer_;
            this->scene_cameras_.emplace_back(camera);

            GameNodeDescription gndesc;
            gndesc.type = GameNodeType::Transform;
            auto gn = GameNodeFactory::Create(gndesc);
            gn->AttachComponent(camera);
            this->AddChild(gn);

            PRINT("num of cameras: " << this->scene_cameras_.size());
        }
        void Scene::CreateMaterials(const aiScene* scene)
        {
            auto vs_file = ResourceLoader::GetInstance().GetFilePath("vs.hlsl");
            auto ps_file = ResourceLoader::GetInstance().GetFilePath("ps.hlsl");
            for (uint32_t mid = 0; mid < scene->mNumMaterials; ++mid)
            {
                auto ai_mat = scene->mMaterials[mid];
                auto mat = std::make_shared<Material>(vs_file, ps_file);
                mat->Load();
                this->scene_materials_.emplace_back(mat);
                aiString szPath;
                if (AI_SUCCESS == ai_mat->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), szPath))
                {
                    std::filesystem::path p = this->file_path_;
                    auto dir = p.parent_path();
                    auto texture_path = dir / std::string(szPath.data);
                    if(this->scene_textures_.find(texture_path.string()) == this->scene_textures_.end())
                    {
                        std::vector<byte> out;

                        uint32_t width;
                        uint32_t height;
                        auto error = lodepng::decode(out, width, height, texture_path.string());
                        CHECK_ASSERT(error == 0);

                        TextureDescriptor tdesc;
                        tdesc.width = width;
                        tdesc.height = height;
                        tdesc.depth = 1;
                        tdesc.format = DataFormat::RGBA32;
                        tdesc.dimension = TextureDimension::TD_2D;
                        tdesc.type = GraphicsResourceType::TextureR;
                        tdesc.usage = GraphicsResourceUsage::GPU_Read_Only;
                        tdesc.resource.data = out.data();
                        tdesc.resource.pitch = sizeof(byte) * 4 * width;
                        tdesc.slot = GraphicsBufferSlot::Slot0;

                        auto tex = Context::GetInstance().GetRenderEngine().Create(tdesc);
                        this->scene_textures_[texture_path.string()] = tex;
                        PRINT(texture_path.relative_path().string() << " Loaded");
                    }

                    mat->textures_.push_back(this->scene_textures_[texture_path.string()]);
                }
            }
            if (this->scene_materials_.size() == 0)
            {
                PRINT("no materials for scene, add a default material");
                auto mat = std::make_shared<Material>(vs_file, ps_file);
                mat->Load();
                this->scene_materials_.emplace_back(mat);
            }
            PRINT("num of materials: " << this->scene_materials_.size());
        }
        void Scene::CreateTextures(const aiScene* scene)
        {
            for (uint32_t tid = 0; tid < scene->mNumTextures; ++tid)
            {
                auto ai_texture = scene->mTextures[tid];
                UNUSED_PARAMETER(ai_texture);
                // std::vector<byte> out;
                // uint32_t width;
                // uint32_t height;
                // auto error = lodepng::decode(out, width, height, "sponza/textures/background.png");
                // CHECK_ASSERT(errno == 0);

                // this->scene_materials_.emplace_back(mat);
            }
            PRINT("num of textures: " << this->scene_textures_.size());
        }
        void Scene::CreateMeshes(const aiScene* scene)
        {
            for (uint32_t mid = 0; mid < scene->mNumMeshes; ++mid)
            {
                auto mesh = scene->mMeshes[mid];

                auto hasPos = mesh->HasPositions();
                auto hasUV = mesh->HasTextureCoords(0);
                auto hasNormal = mesh->HasNormals();
                auto hasBones = mesh->HasBones();

                std::vector<Vertex> vd;
                std::vector<uint32_t> id;

                for (uint32_t i = 0; i < mesh->mNumVertices; ++i)
                {
                    Vertex v;
                    v.pos = hasPos ? float3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z) : float3(0, 0, 0);
                    // v.pos *= 0.2f;
                    // v.pos.z() = 0;
                    v.normal = hasNormal ? float3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z) : float3(0, 0, 0);
                    v.uv = hasUV ? float2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y) : float2(0, 0);
                    v.color = float4(1, 1, 1, 1);

                    vd.emplace_back(v);
                }

                for (uint32_t i = 0; i < mesh->mNumFaces; ++i)
                {
                    auto f = mesh->mFaces[i];
                    for (uint32_t fi = 0; fi < f.mNumIndices; ++fi)
                    {
                        id.emplace_back(f.mIndices[fi]);
                    }
                }
                if(hasBones)
                {
                    GameNodeDescription desc;
                    desc.type = GameNodeType::Skeleton;
                    auto skeleton = GameNodeFactory::Create(desc);
                    for (uint32_t b = 0; b < mesh->mNumBones; ++b)
                    {
                        PRINT(mesh->mName.data << " has bones " << mesh->mBones[b]->mName.data << " with " << mesh->mBones[b]->mNumWeights << " weights");
                        // mesh->mBones[b]->mOffsetMatrix will transform vertex from model space to pose/joint local space;
                        // aiBone's document is confusing
                        // https://learnopengl.com/Guest-Articles/2020/Skeletal-Animation is CORRECT
                        auto bone = mesh->mBones[b];

                        desc.type = GameNodeType::Joint;
                        auto joint = std::dynamic_pointer_cast<Animation::Joint>(GameNodeFactory::Create(desc));
                        joint->name_ = bone->mName.data;
                        // joint->inverse_bind_pos_matrix_ = bone->mOffsetMatrix;
                        for(uint32_t wid = 0; wid < bone->mNumWeights; ++wid)
                        {
                            auto aiWeight = bone->mWeights[wid];
                            Animation::VertexWeight w;
                            w.index = aiWeight.mVertexId;
                            w.weight = aiWeight.mWeight;
                            joint->weights.emplace_back(w);
                        }

                        this->mesh_joints_[mesh->mName.data][joint->name_] = joint;
                    }
                }
                GameObjectDescription desc;
                desc.type = GameObjectType::Mesh;
                auto mesh_go = GameObjectFactory::Create<Mesh>(desc, vd, id);
                this->scene_meshes_.emplace_back(mesh_go);
            }

            PRINT("num of meshes: " << this->scene_meshes_.size());
        }
        void Scene::CreateAnimations(const aiScene* scene)
        {
            for(uint32_t i = 0; i < scene->mNumAnimations; ++i)
            {
                //each animation is an AnimationClip
                auto anim = scene->mAnimations[i];
                PRINT("handling animation" << anim->mName.data)
                for(uint32_t c = 0; c < anim->mNumChannels; ++c)
                {
                    //Each channel defines node/bone it controls
                    //for example
                    //node->mNodeName = "Torso" contains key frames data for "Torso" Node/Bone in the scene
                    //mNodeName could be aiNode or aiBone
                    auto node = anim->mChannels[c];
                    PRINT("channel " << node->mNodeName.data << " has " << node->mNumPositionKeys << " Key frame");
                }

            }

        }



        GameNodeSharedPtr Scene::HandleNode(const aiNode* node, const aiScene* scene)
        {
            GameNodeSharedPtr game_node = nullptr;

            std::string mesh_name;
            if (this->IsJoint(node, mesh_name))
            {
                game_node = this->mesh_joints_[mesh_name][node->mName.data];
                if (this->mesh_root_joint_.find(mesh_name) == this->mesh_root_joint_.end()) 
                {
                    this->mesh_root_joint_[mesh_name] = std::dynamic_pointer_cast<Animation::Joint>(game_node);
                }
            }
            else
            {
                GameNodeDescription desc;
                desc.type = GameNodeType::Transform;
                game_node = GameNodeFactory::Create(desc);
            }

            game_node->name_ = node->mName.data;
            //set transformation here
            auto transform = node->mTransformation;
            // parent->AddChild(game_node);
            std::string parentName = "None";
            if(node->mParent != nullptr) parentName = node->mParent->mName.data;

            PRINT("aiNode " << node->mName.data << " parent :" << parentName);
            for (uint32_t i = 0; i < node->mNumMeshes; ++i)
            {
                GameNodeDescription desc;
                auto mesh_node = GameNodeFactory::Create(desc);
                // scene_meshes_ contains same mesh data as they are in aiScene
                auto scene_mesh_id = node->mMeshes[i];

                auto ai_mesh = scene->mMeshes[scene_mesh_id];
                auto mesh = this->scene_meshes_[scene_mesh_id];
                PRINT("aiNode " << node->mName.data << " with ai mesh name " << ai_mesh->mName.data);

                ComponentDescription cdesc;
                auto mesh_component = GameNodeFactory::Create<MeshComponent>(cdesc, mesh);
                mesh_node->AttachComponent(mesh_component);

                // add skeleton to mesh node
                // mesh_node->AddChild(skeleton)

                auto mesh_renderer = GameNodeFactory::Create<MeshRendererComponent>(cdesc);
                mesh_node->AttachComponent(mesh_renderer);

                auto mat = this->scene_materials_[ai_mesh->mMaterialIndex];
                mesh_renderer->GO()->material_ = mat;

                // auto s = 2.0f;
                // mesh_node->Transform()->Scale() = float3(s, s, s);
                // mesh_node->Transform()->Translate() = float3(0, 0, 1);

                game_node->AddChild(mesh_node);
            }

            for (uint32_t c = 0; c < node->mNumChildren; ++c)
            {
                auto child = this->HandleNode(node->mChildren[c], scene);
                game_node->AddChild(child);
            }

            return game_node;
        }
        void Scene::Update()
        {
            this->TraverseAllChildren<TransformComponent>(
                [&](TransformComponentSharedPtr node)
                {
                    // node->UpdateLocal(parent);
                    node->OnUpdate();

                    // auto pos = node->game_object_->Translate();
                    // PRINT(pos.x() << " " << pos.y());
                    // PRINT(node->name_);
                    return true;
                });
            // camera
            // frame
            // flush each scene object
            // render each matrial pass for every object
            // this->root_->UpdateLocal(nullptr);
            // this->Traverse<GameNode>(
            //     [&](GameNodeSharedPtr node, const GameNodeSharedPtr parent)
            //     {
            //         // node->UpdateLocal(parent);
            //         return true;
            //     });

            for (auto& c : this->scene_cameras_)
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
            }
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
        void Scene::AddTestNode()
        {
            auto vs_file = "shader/vs.hlsl";
            auto ps_file = "shader/ps.hlsl";
            auto mat = std::make_shared<Material>(vs_file, ps_file);
            mat->Load();

            auto gn = std::make_shared<GameNode>();

            auto mrc = std::make_shared<Rendering::MeshRendererComponent>();
            mrc->GO()->material_ = mat;
            gn->AttachComponent(mrc);
            auto mc = std::make_shared<Rendering::MeshComponent>();
            mc->GO()->Load("bunny.obj");
            gn->AttachComponent(mc);

            // auto s = 2.0f;
            // gn->SetScale(float3(s,s,s));
            // gn->SetPos(float3(0.1f,0,1));
            // mp->game_object_ = std::make_shared<Rendering::MeshRenderer>();
            // auto mp = std::make_shared<MeshRendererComponent>();
            // auto mp = std::make_shared<MeshComponent>();
            this->AddToSceneNode(gn);

            auto camera = std::make_shared<CameraComponent>();
            camera->GO()->target = Context::GetInstance().GetRenderEngine().back_buffer_;
            this->AddToSceneNode(camera);
        }
        void Scene::AddToSceneNode(const GameNodeSharedPtr new_node, const GameNodeSharedPtr game_node /*= nullptr*/)
        {
            auto camera = std::dynamic_pointer_cast<CameraComponent>(new_node);
            if (camera != nullptr)
            {
                this->scene_cameras_.emplace_back(camera);
            }

            if (game_node == nullptr)
            {
                this->AddChild(new_node);
            }
            else
            {
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
            }
        }
    }  // namespace Core

}  // namespace vEngine