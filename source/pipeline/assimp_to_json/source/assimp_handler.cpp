
#include <assimp_handler.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <external/lodepng.h>
#include <external/tga.h>

#include <vengine/core/game_object_factory.hpp>
#include <vengine/core/scene.hpp>

namespace vEngine
{
    namespace Pipeline
    {
        using namespace Core;
        using namespace Rendering;
        using namespace Animation;

        SceneSharedPtr AssimpHandler::LoadFromAssimp(const std::filesystem::path file_path)
        {
            Assimp::Importer importer;
            auto ai_scene = importer.ReadFile(file_path.string(), aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
            auto scene = GameObjectFactory::Create<Scene>();



            this->HandleMeshes(scene, ai_scene);
            this->HandleMaterials(scene, ai_scene);
            // this->CreateTextures(scene);
            this->HandleCameras(scene, ai_scene);
            this->HandleAnimations(scene, ai_scene);

            this->root_ = this->HandleNode(scene->mRootNode, scene);

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

            PRINT("num of cameras: " << this->cameras_.size());
        }
        void AssimpHandler::HandleMaterials(const aiScene* scene)
        {
            for (uint32_t mid = 0; mid < scene->mNumMaterials; ++mid)
            {
                auto ai_mat = scene->mMaterials[mid];
                auto mat = GameObjectFactory::Create<Material>();
                auto rdesc = std::make_shared<MaterialResourceDesc>();
                rdesc->shaders[ShaderType::VS] = vs_file;
                rdesc->shaders[ShaderType::PS] = ps_file;
                mat->Load(rdesc);
                this->materials_.emplace_back(mat);
                aiString szPath;
                if (AI_SUCCESS == ai_mat->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), szPath))
                {
                    auto texture_path = std::filesystem::path(ResourceLoader::GetInstance().GetFilePath(szPath.data));
                    if (this->textures_.find(texture_path.string()) == this->textures_.end())
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

                        auto tex = Context::GetInstance().GetRenderEngine().Create(tdesc);
                        this->textures_[texture_path.string()] = tex;
                        PRINT(texture_path.relative_path().string() << " Loaded");
                    }

                    mat->textures_.push_back(this->textures_[texture_path.string()]);
                }
            }
            if (this->materials_.size() == 0)
            {
                PRINT("no materials for scene, add a default material");
                auto mat = GameObjectFactory::Default<Material>();
                this->materials_.emplace_back(mat);
            }
            PRINT("num of materials: " << this->materials_.size());
        }
        std::vector<MeshSharedPtr> HandleMeshes(const aiScene* scene) {}
        std::vector<AnimationClipSharedPtr> HandleAnimations(const aiScene* scene) {}
    }  // namespace Pipeline
}  // namespace vEngine