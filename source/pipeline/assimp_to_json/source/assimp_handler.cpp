
#include <assimp_handler.hpp>

#include <external/lodepng.h>
#include <external/tga.h>

#include <vengine/core/game_object_factory.hpp>
#include <vengine/core/scene.hpp>
#include <vengine/core/mesh.hpp>
#include <vengine/core/resource_loader.hpp>
#include <vengine/rendering/shader.hpp>
#include <vengine/rendering/material.hpp>
#include <vengine/rendering/texture.hpp>

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

            // this->root_ = this->HandleNode(scene->mRootNode, scene);

            return scene;
        }
        void AssimpHandler::HandleCameras(SceneSharedPtr scene, const aiScene* ai_scene)
        {
            UNUSED_PARAMETER(scene);
            UNUSED_PARAMETER(ai_scene);
            // ComponentDescription desc;
            // auto camera = GameNodeFactory::Create<CameraComponent>(desc);
            // camera->GO()->target = Context::GetInstance().GetRenderEngine().back_buffer_;

            // GameNodeDescription gndesc;
            // gndesc.type = GameNodeType::Transform;
            // auto gn = GameNodeFactory::Create(gndesc);
            // gn->AttachComponent(camera);
            // this->cameras_.emplace_back(gn);
            if (scene->cameras_.size() == 0)
            {
                // auto cam = GameObjectFactory::Default<Camera>();
                // cam->target = Context::GetInstance().GetRenderEngine().back_buffer_;
                // this->cameras_.emplace_back(cam);
            }

            // PRINT("num of cameras: " << this->cameras_.size());
        }
        void AssimpHandler::HandleMaterials(Core::SceneSharedPtr scene, const aiScene* ai_scene)
        {
            UNUSED_PARAMETER(scene);
            UNUSED_PARAMETER(ai_scene);
            auto vs = GameObjectFactory::Create<Shader>();
            auto vs_desc = std::make_shared<ResourceDescriptor>();
            vs_desc->file_path = ResourceLoader::GetInstance().GetFilePath("vs.hlsl");
            vs->Load(vs_desc);
            vs->type = ShaderType::VS;

            auto ps = GameObjectFactory::Create<Shader>();
            auto ps_desc = std::make_shared<ResourceDescriptor>();
            ps_desc->file_path = ResourceLoader::GetInstance().GetFilePath("ps.hlsl");
            ps->Load(ps_desc);
            ps->type = ShaderType::PS;

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
                        // tdesc.raw_data = out;
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

                        auto tex = Context::GetInstance().GetRenderEngine().Create(tdesc);
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

                    PRINT(ai_mesh->mName.data << " has bones/joint " << name << " with " << ai_bone->mNumWeights);

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
        void AssimpHandler::HandleAnimations(Core::SceneSharedPtr scene, const aiScene* ai_scene)
        {
            UNUSED_PARAMETER(scene);
            UNUSED_PARAMETER(ai_scene);
        }
    }  // namespace Pipeline
}  // namespace vEngine