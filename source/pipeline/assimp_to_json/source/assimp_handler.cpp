
#include <assimp_handler.hpp>

#include <external/lodepng.h>
#include <external/tga.h>

#include <vengine/core/game_object_factory.hpp>
#include <vengine/core/scene.hpp>
#include <vengine/core/camera_component.hpp>
#include <vengine/core/transform_component.hpp>
#include <vengine/core/mesh_component.hpp>
#include <vengine/rendering/mesh_renderer_component.hpp>
#include <vengine/core/resource_loader.hpp>
#include <vengine/rendering/shader.hpp>
#include <vengine/rendering/material.hpp>
#include <vengine/rendering/texture.hpp>

#include <vengine/animation/bone_component.hpp>
#include <vengine/animation/joint.hpp>
#include <vengine/animation/animation_clip.hpp>
#include <vengine/animation/animator_component.hpp>

#include <vengine/core/context.hpp>
#include <vengine/rendering/render_engine.hpp>

namespace vEngine
{
    namespace Pipeline
    {
        using namespace Core;
        using namespace Rendering;
        using namespace Animation;

        SceneSharedPtr AssimpHandler::LoadFromAssimp(const std::filesystem::path path)
        {
            ResourceLoader::GetInstance().DumpCurrentPath();

            Assimp::Importer importer;
            auto ai_scene = importer.ReadFile(path.string(), aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
            auto scene = GameObjectFactory::Create<Scene>();

            this->HandleMeshes(scene, ai_scene);
            this->HandleMaterials(scene, ai_scene);
            // // this->CreateTextures(scene);
            this->HandleCameras(scene, ai_scene);
            this->HandleAnimations(scene, ai_scene);

            auto root = this->HandleNode(scene, ai_scene->mRootNode, ai_scene);
            scene->AddChild(root);

            return scene;
        }
        void AssimpHandler::HandleCameras(SceneSharedPtr scene, const aiScene* ai_scene)
        {
            // UNUSED_PARAMETER(scene);
            UNUSED_PARAMETER(ai_scene);

            auto gn = GameObjectFactory::Create<GameNode>();

            auto camera = GameObjectFactory::Create<CameraComponent>();
            camera->GO()->target = Context::GetInstance().GetRenderEngine()->back_buffer_;

            auto transform = GameObjectFactory::Create<TransformComponent>();

            gn->AttachComponent(camera);
            gn->AttachComponent(transform);

            scene->AddChild(gn);

            // scene->AddCamera(camera);
            // if (scene->cameras_.size() == 0)
            {
                // auto cam = GameObjectFactory::Default<Camera>();
                // cam->target = Context::GetInstance().GetRenderEngine().back_buffer_;
                // this->cameras_.emplace_back(cam);
            }

            // PRINT("num of cameras: " << this->cameras_.size());
        }
        void AssimpHandler::HandleMaterials(SceneSharedPtr scene, const aiScene* ai_scene)
        {
            auto vs = GameObjectFactory::Default<Shader>(ShaderType::VS);
            auto ps = GameObjectFactory::Default<Shader>(ShaderType::PS);

            for (uint32_t mid = 0; mid < ai_scene->mNumMaterials; ++mid)
            {
                auto ai_mat = ai_scene->mMaterials[mid];
                auto mat = GameObjectFactory::Create<Material>();
                mat->BindShader(ShaderType::VS, vs);
                mat->BindShader(ShaderType::PS, ps);

                scene->AddMaterial(mat);
                
                aiString szPath;
                if (AI_SUCCESS == ai_mat->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), szPath))
                {
                    auto texture_path = ResourceLoader::GetInstance().GetFilePath(szPath.data);
                    if (!scene->HasTexture(texture_path.string()))
                    {
                        std::vector<byte> out;

                        uint32_t width = 0;
                        uint32_t height = 0;
                        auto format = DataFormat::RGBA32;
                        if (texture_path.extension() == ".png")
                        {
                            auto error = lodepng::decode(out, width, height, texture_path.string());
                            CHECK_ASSERT(error == 0);
                        }
                        else if (texture_path.extension() == ".tga")
                        {
                            FILE* f;
                            auto error = fopen_s(&f, texture_path.string().c_str(), "rb");
                            CHECK_ASSERT(error == 0);

                            tga::StdioFileInterface file(f);
                            tga::Decoder decoder(&file);
                            tga::Header header;
                            if (!decoder.readHeader(header)) CHECK_ASSERT(false);

                            tga::Image image;
                            image.bytesPerPixel = header.bytesPerPixel();
                            image.rowstride = header.width * header.bytesPerPixel();

                            out.resize(image.rowstride * header.height);
                            image.pixels = &out[0];

                            if (!decoder.readImage(header, image, nullptr)) CHECK_ASSERT(false);

                            width = header.width;
                            height = header.height;
                        }
                        else
                        {
                            PRINT_AND_BREAK("texture file " << texture_path << " not supported");
                        }

                        TextureDescriptor tdesc;
                        tdesc.width = width;
                        tdesc.height = height;
                        tdesc.depth = 1;
                        tdesc.format = format;
                        tdesc.dimension = TextureDimension::TD_2D;
                        tdesc.type = GraphicsResourceType::TextureR;
                        tdesc.usage = GraphicsResourceUsage::GPU_Read_Only;
                        tdesc.resource.data = out.data();
                        tdesc.resource.pitch = sizeof(byte) * GetByteSize(format) * width;
                        tdesc.slot = GraphicsBufferSlot::Slot0;

                        auto tex = Context::GetInstance().GetRenderEngine()->Create(tdesc);
                        tex->SetRawData(out);
                        scene->SetTexture(texture_path.string(), tex);

                        PRINT(texture_path.relative_path().string() << " Loaded");
                    }

                    mat->BindTexture("diffuse", scene->GetTexture(texture_path.string()));
                }
            }
            // if (this->materials_.size() == 0)
            // {
            //     PRINT("no materials for scene, add a default material");
            //     auto mat = GameObjectFactory::Default<Material>();
            //     this->materials_.emplace_back(mat);
            // }
            // PRINT("num of materials: " << this->materials_.size());
        }
        float4x4 AssimpHandler::AiMatrixToFloat4x4(aiMatrix4x4 mat)
        {
            return Math::Transpose(float4x4(mat[0][0], mat[0][1], mat[0][2], mat[0][3], mat[1][0], mat[1][1], mat[1][2], mat[1][3], mat[2][0], mat[2][1], mat[2][2], mat[2][3], mat[3][0], mat[3][1],
                                            mat[3][2], mat[3][3]));
        }
        void AssimpHandler::HandleMeshes(SceneSharedPtr scene, const aiScene* ai_scene)
        {
            CHECK_ASSERT_NOT_NULL(scene);
            CHECK_ASSERT_NOT_NULL(ai_scene);

            for (uint32_t mid = 0; mid < ai_scene->mNumMeshes; ++mid)
            {
                auto ai_mesh = ai_scene->mMeshes[mid];
                auto mesh = GameObjectFactory::Create<Mesh>();

                std::vector<Vertex> vertices;
                std::vector<uint32_t> indices;

                auto hasPos = ai_mesh->HasPositions();
                auto hasUV = ai_mesh->HasTextureCoords(0);
                auto hasNormal = ai_mesh->HasNormals();
                for (uint32_t i = 0; i < ai_mesh->mNumVertices; ++i)
                {
                    Vertex v;
                    v.pos = hasPos ? float3(ai_mesh->mVertices[i].x, ai_mesh->mVertices[i].y, ai_mesh->mVertices[i].z) : float3(0, 0, 0);
                    v.normal = hasNormal ? float3(ai_mesh->mNormals[i].x, ai_mesh->mNormals[i].y, ai_mesh->mNormals[i].z) : float3(0, 0, 0);
                    v.uv = hasUV ? float2(ai_mesh->mTextureCoords[0][i].x, ai_mesh->mTextureCoords[0][i].y) : float2(0, 0);
                    v.color = float4(1, 1, 1, 1);

                    v.bone_id_0 = v.bone_id_1 = int4(-1, -1, -1, -1);
                    v.bone_weight_0 = v.bone_weight_1 = float4::Zero();

                    vertices.emplace_back(v);
                }
                for (uint32_t i = 0; i < ai_mesh->mNumFaces; ++i)
                {
                    auto f = ai_mesh->mFaces[i];
                    for (uint32_t fi = 0; fi < f.mNumIndices; ++fi)
                    {
                        indices.emplace_back(f.mIndices[fi]);
                    }
                }

                mesh->SetVertexData(vertices, indices);

                for (uint32_t bid = 0; bid < ai_mesh->mNumBones; ++bid)
                {
                    // mesh->mBones[b]->mOffsetMatrix will transform vertex from model space to pose/joint local space;
                    // aiBone's document is confusing
                    // https://learnopengl.com/Guest-Articles/2020/Skeletal-Animation is CORRECT
                    auto ai_bone = ai_mesh->mBones[bid];

                    auto name = ai_bone->mName.data;
                    auto offset = this->AiMatrixToFloat4x4(ai_bone->mOffsetMatrix);
                    auto weights = std::vector<VertexWeight>();

                    PRINT(ai_mesh->mName.data << " has bones/joint " << name << " with weight count" << ai_bone->mNumWeights);

                    for (uint32_t wid = 0; wid < ai_bone->mNumWeights; ++wid)
                    {
                        auto aiWeight = ai_bone->mWeights[wid];
                        VertexWeight w;
                        w.index = aiWeight.mVertexId;
                        w.weight = aiWeight.mWeight;
                        weights.emplace_back(w);
                    }

                    mesh->SetBoneData(name, bid, weights, offset);
                }
                scene->SetMesh(mid, mesh);
            }

        }
        void AssimpHandler::HandleAnimations(SceneSharedPtr scene, const aiScene* ai_scene)
        {
            for (uint32_t i = 0; i < ai_scene->mNumAnimations; ++i)
            {
                auto animation = GameObjectFactory::Create<AnimationClip>();
                // each animation is an AnimationClip
                auto anim = ai_scene->mAnimations[i];

                animation->descriptor_.name = anim->mName.data;
                animation->Duration() = static_cast<float>(anim->mDuration);
                animation->TicksPerSecond() = static_cast<float>(anim->mTicksPerSecond);
                animation->TotalFrame() = Math::FloorToInt(anim->mDuration * anim->mTicksPerSecond);
                PRINT("handling " << animation->descriptor_.name << " animation with " << animation->TotalFrame() << " frames")
                for (uint32_t c = 0; c < anim->mNumChannels; ++c)
                {
                    // Each channel defines node/bone it controls
                    // for example
                    // node->mNodeName = "Torso" contains key frames data for "Torso" Node/Bone in the scene
                    // mNodeName could be aiNode or aiBone
                    auto node = anim->mChannels[c];
                    PRINT("channel " << node->mNodeName.data << " has " << node->mNumPositionKeys << " Key values");

                    auto joint = GameObjectFactory::Create<Joint>();
                    joint->descriptor_.name = node->mNodeName.data;

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
                    animation->AddJoint(joint->descriptor_.name, joint);
                }

                scene->AddAnimation(animation);
            }
        }

        void AssimpHandler::HandleBoneNode(SceneSharedPtr scene, const aiNode* ai_node, const GameNodeSharedPtr game_node)
        {
            if (ai_node == nullptr) return;

            auto bone_name = ai_node->mName.data;
            for (const auto& m : scene->meshes_)
            {
                if (m.second->bone_data_.find(bone_name) != m.second->bone_data_.end())
                {
                    // TODO Add init/bind pose pos/rotation/scale to bone_comp
                    auto bone_comp = m.second->bone_data_[bone_name];
                    game_node->AttachComponent(bone_comp);
                }
            }

        }
        GameNodeSharedPtr AssimpHandler::HandleNode(SceneSharedPtr scene, const aiNode* ai_node, const aiScene* ai_scene)
        {
            auto node = GameObjectFactory::Create<GameNode>();
            auto transform = GameObjectFactory::Create<TransformComponent>();
            node->AttachComponent(transform);
            node->descriptor_.name = ai_node->mName.data;

            this->HandleBoneNode(scene, ai_node, node);

            node->descriptor_.name = ai_node->mName.data;
            // set transformation here
            // auto transform = ai_node->mTransformation;
            // parent->AddChild(game_node);
            std::string parentName = "None";
            if (ai_node->mParent != nullptr) parentName = ai_node->mParent->mName.data;
            PRINT("aiNode " << ai_node->mName.data << " parent :" << parentName);

            for (uint32_t i = 0; i < ai_node->mNumMeshes; ++i)
            {
                auto mesh_node = GameObjectFactory::Create<GameNode>();
                auto mesh_transform = GameObjectFactory::Create<TransformComponent>();
                mesh_node->AttachComponent(mesh_transform);
                // scene_meshes_ contains same mesh data as they are in aiScene
                auto scene_mesh_id = ai_node->mMeshes[i];

                auto ai_mesh = ai_scene->mMeshes[scene_mesh_id];
                auto mesh = scene->meshes_[scene_mesh_id];
                PRINT("aiNode " << ai_node->mName.data << " with ai mesh name " << ai_mesh->mName.data);

                auto mesh_component = GameObjectFactory::Create<MeshComponent>();
                mesh_component->Reset(mesh);
                mesh_node->AttachComponent(mesh_component);

                auto mesh_renderer = GameObjectFactory::Create<MeshRendererComponent>();
                mesh_node->AttachComponent(mesh_renderer);

                auto mat = scene->materials_[ai_mesh->mMaterialIndex];
                mesh_renderer->GO()->material_ = mat;

                node->AddChild(mesh_node);
            }

            for (uint32_t c = 0; c < ai_node->mNumChildren; ++c)
            {
                auto child = this->HandleNode(scene, ai_node->mChildren[c], ai_scene);
                node->AddChild(child);
            }

            return node;
        }
    }  // namespace Pipeline
}  // namespace vEngine