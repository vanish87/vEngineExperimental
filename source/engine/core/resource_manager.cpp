/// \file resource_manager.cpp
/// \brief source file for Resource Manager
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/resource_manager.hpp>
#include <vengine/core/game_object_factory.hpp>
#include <vengine/core/game_node.hpp>
#include <vengine/data/json.hpp>

// #include <vengine/animation/bone_component.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    /// constructor detailed defintion,
    /// should be 2 lines
    namespace Core
    {
        ResourceManager::ResourceManager()
        {
            this->loading_thread_.Create();
        }
        ResourceManager::~ResourceManager()
        {
            this->loading_thread_.Quit();
            this->loading_thread_.Join();
        }
        void ResourceManager::Init()
        {
            auto config = Context::GetInstance().CurrentConfigure();
            auto path = config.resource_bin / config.context_name / "uuid.json";
            if (!std::filesystem::exists(path)) return;

            auto j = LoadJson(path);
            FromJson(j, UUIDGenerator::GetInstance());
        }
        void ResourceManager::Deinit()
        {
            auto config = Context::GetInstance().CurrentConfigure();
            auto path = config.resource_bin / config.context_name / "uuid.json";
            auto j = ToJson(UUIDGenerator::GetInstance());
            SaveJson(j, path);

            this->runtime_objects_.clear();
        }

        void ResourceManager::LoadAsync(const ResourceDescriptor& desc)
        {
            this->loading_thread_.AddToQueue(std::make_shared<ResourceLoadingJob>(desc));
        }
        void ResourceManager::Load(const ResourceDescriptor& desc)
        {
            desc.on_load_call_back();
        }

        std::filesystem::path ResourceManager::GetFilePath(const std::string file_name)
        {
            auto config = Context::GetInstance().CurrentConfigure();
            auto root = config.resource_src;
            for (const auto& file : std::filesystem::recursive_directory_iterator{root})
            {
                if (file.is_regular_file() && file.path().filename() == file_name)
                {
                    return file.path();
                }
            }

            CHECK_AND_ASSERT(false, "Cannot find file/folder " << file_name);
            return std::filesystem::path(file_name);
        }

        // Save to a None-Context folder
        void ResourceManager::Save(const GameObjectSharedPtr go, const std::filesystem::path path)
        {
            auto j = ToJson(go);
            SaveJson(j, path);
        }
        void ResourceManager::AddPendingSave(const GameObjectSharedPtr go)
        {
            const auto k = go->descriptor_.uuid;
            const auto v = go;
            if(this->pending_uuids_.find(k) != this->pending_uuids_.end()) return;

            this->UpdateReferencePath(v);
            this->pending_uuids_.insert(k);
            this->pending_objects_.push(v);
        }
        void ResourceManager::FlushPending()
        {
            auto count = 0;
            while (!this->pending_objects_.empty())
            {
                const auto go = this->pending_objects_.top();
                this->pending_objects_.pop();
                // ResourceDescriptor desc;
                // desc.on_load_call_back =([&]()
                // {
                    this->Save(go);
                // });
                // this->LoadAsync(desc);
                count++;
            }
            PRINT("The num of pending objects saved " << count);
        }
        void ResourceManager::Save(const GameObjectSharedPtr go)
        {
            #define CASE_AND_SAVE(etype, type)                      \
                case etype:                                         \
                {                                                   \
                    auto sub = std::dynamic_pointer_cast<type>(go); \
                    SaveJson(ToJson(*sub.get()), path);             \
                }                                                   \
                break;

            auto type = go->descriptor_.type;
            auto path = this->GetGameObjectPath(go->descriptor_);

            if (type == GameObjectType::Component) CHECK_AND_ASSERT(false, "Cannot create component without game object type");
            if (type == GameObjectType::Renderer) CHECK_AND_ASSERT(false, "Cannot create component without game object type");
            if (type == GameObjectType::RendererComponent) CHECK_AND_ASSERT(false, "Cannot create component without game object type");
            switch (type)
            {
                CASE_AND_SAVE(GameObjectType::GameObject, GameObject);
                CASE_AND_SAVE(GameObjectType::GameNode, GameNode);
                CASE_AND_SAVE(GameObjectType::Transform, Transform);
                CASE_AND_SAVE(GameObjectType::TransformComponent, TransformComponent);
                CASE_AND_SAVE(GameObjectType::Camera, Camera);
                CASE_AND_SAVE(GameObjectType::CameraComponent, CameraComponent);
                CASE_AND_SAVE(GameObjectType::Light, Light);
                CASE_AND_SAVE(GameObjectType::LightComponent, CameraComponent);
                CASE_AND_SAVE(GameObjectType::Mesh, Mesh);
                CASE_AND_SAVE(GameObjectType::MeshComponent, MeshComponent);
                CASE_AND_SAVE(GameObjectType::Scene, Scene);

                // CASE_AND_SAVE(GameObjectType::Serializer, Data::Serializer);

                CASE_AND_SAVE(GameObjectType::MeshRenderer, Rendering::MeshRenderer);
                CASE_AND_SAVE(GameObjectType::MeshRendererComponent, Rendering::MeshRendererComponent);
                CASE_AND_SAVE(GameObjectType::Material, Rendering::Material);
                CASE_AND_SAVE(GameObjectType::Texture, Rendering::Texture);
                CASE_AND_SAVE(GameObjectType::PipelineState, Rendering::PipelineState);
                CASE_AND_SAVE(GameObjectType::Shader, Rendering::Shader);

                CASE_AND_SAVE(GameObjectType::GraphicsBuffer, Rendering::GraphicsBuffer);

                CASE_AND_SAVE(GameObjectType::Bone, Animation::Bone);
                CASE_AND_SAVE(GameObjectType::BoneComponent, Animation::BoneComponent);
                CASE_AND_SAVE(GameObjectType::Joint, Animation::Joint);
                CASE_AND_SAVE(GameObjectType::AnimationClip, Animation::AnimationClip);
                CASE_AND_SAVE(GameObjectType::Animator, Animation::Animator);
                CASE_AND_SAVE(GameObjectType::AnimatorComponent, Animation::AnimatorComponent);
                default:
                    // PRINT(ToString(type));
                    NOT_IMPL_ASSERT;
                    break;
            }
            #undef CASE_AND_SAVE
        }
        GameObjectSharedPtr ResourceManager::Load(const GameObjectDescriptor& desc)
        {
            #define CASE_AND_CREATE(ptr, etype, type)                                   \
                case etype:                                                             \
                {                                                                       \
                    auto go = GameObjectFactory::Create<etype, type>();                 \
                    auto path = ResourceManager::GetInstance().GetGameObjectPath(desc); \
                    auto j = LoadJson(path);             \
                    FromJson(j, *go.get());                                             \
                    ptr = go;                                                           \
                }                                                                       \
                break;

            #define CASE_AND_CREATE_ARG(ptr, etype, type, args)                         \
                case etype:                                                             \
                {                                                                       \
                    auto go = GameObjectFactory::Create<etype, type>(args);             \
                    auto path = ResourceManager::GetInstance().GetGameObjectPath(desc); \
                    auto j = LoadJson(path);             \
                    FromJson(j, *go.get());                                             \
                    ptr = go;                                                           \
                }                                                                       \
                break;

            GameObjectSharedPtr shared;

            switch (desc.type)
            {
                CASE_AND_CREATE(shared, GameObjectType::GameObject, GameObject);
                CASE_AND_CREATE(shared, GameObjectType::GameNode, GameNode);
                // CASE_AND_CREATE(shared, GameObjectType::Component, GameNode);
                CASE_AND_CREATE(shared, GameObjectType::Transform, Transform);
                CASE_AND_CREATE(shared, GameObjectType::TransformComponent, TransformComponent);
                CASE_AND_CREATE(shared, GameObjectType::Camera, Camera);
                CASE_AND_CREATE(shared, GameObjectType::CameraComponent, CameraComponent);
                CASE_AND_CREATE(shared, GameObjectType::Light, Light);
                CASE_AND_CREATE(shared, GameObjectType::LightComponent, LightComponent);
                CASE_AND_CREATE(shared, GameObjectType::Mesh, Mesh);
                CASE_AND_CREATE(shared, GameObjectType::MeshComponent, MeshComponent);
                CASE_AND_CREATE(shared, GameObjectType::Scene, Scene);
                
                // CASE_AND_CREATE(shared, GameObjectType::Serializer, Data::Serializer);


                // CASE_AND_CREATE(shared, GameObjectType::Renderer, Rendering::Renderer);
                CASE_AND_CREATE(shared, GameObjectType::MeshRenderer, Rendering::MeshRenderer);
                CASE_AND_CREATE(shared, GameObjectType::MeshRendererComponent, Rendering::MeshRendererComponent);
                CASE_AND_CREATE(shared, GameObjectType::Material, Rendering::Material);
                CASE_AND_CREATE_ARG(shared, GameObjectType::Texture, Rendering::Texture, Rendering::TextureDescriptor::Default());
                CASE_AND_CREATE_ARG(shared, GameObjectType::PipelineState, Rendering::PipelineState, Rendering::PipelineStateDescriptor::Default());
                CASE_AND_CREATE(shared, GameObjectType::Shader, Rendering::Shader);

                CASE_AND_CREATE(shared, GameObjectType::Bone, Animation::Bone);
                CASE_AND_CREATE(shared, GameObjectType::BoneComponent, Animation::BoneComponent);
                CASE_AND_CREATE(shared, GameObjectType::Joint, Animation::Joint);
                CASE_AND_CREATE(shared, GameObjectType::AnimationClip, Animation::AnimationClip);
                CASE_AND_CREATE(shared, GameObjectType::Animator, Animation::Animator);
                CASE_AND_CREATE(shared, GameObjectType::AnimatorComponent, Animation::AnimatorComponent);
                default:
                    NOT_IMPL_ASSERT;
                    break;
            }

            return shared;

            #undef CASE_AND_CREATE
            #undef CASE_AND_CREATE_ARG
        }
        void ResourceManager::SaveContext()
        {
            for (const auto& rt : this->runtime_objects_)
            {
                this->UpdateReferencePath(rt.second);
            }

            for (const auto& rt : this->runtime_objects_)
            {
                this->Save(rt.second);
            }
        }
        void ResourceManager::Register(const GameObjectSharedPtr go, bool isDynamic)
        {
            UNUSED_PARAMETER(isDynamic);
            // CHECK_ASSERT(this->runtime_objects_.find(go) == std::unordered_map::end());
            this->runtime_objects_[go->descriptor_.uuid] = go;
        }
        GameObjectSharedPtr ResourceManager::Load(const std::filesystem::path path)
        {
            if (!std::filesystem::exists(path)) return nullptr;

            auto j = LoadJson(path);
            GameObjectDescriptor desc;
            FromJson(j["meta"], desc);

            return this->FindOrLoad(desc);
        }

        GameObjectSharedPtr ResourceManager::FindOrLoad(const GameObjectDescriptor& desc)
        {
            auto ret = this->runtime_objects_.find(desc.uuid);
            if(ret == this->runtime_objects_.end())
            {
                return this->Load(desc);
            }
            else
            {
                return ret->second;
            }
        }

        std::filesystem::path ResourceManager::GetGameObjectPath(const GameObjectDescriptor& desc)
        {
            auto name = desc.name;
            auto type = std::string();
            ToString(desc.type, type);

            auto config = Context::GetInstance().CurrentConfigure();
            auto root = config.resource_bin;
            auto file_name = std::to_string(desc.uuid.AsUint()) + "_" + name + "_" + type + ".json";

            std::string illegal = ":\"\'<>%$*&+ ";
            for (auto c : illegal)
            {
                std::replace(file_name.begin(), file_name.end(), c, '_');
            }

            // return root / desc.reference_path / file_name;
            return root / config.context_name / file_name;
        }
        void ResourceManager::UpdateReferencePath(const GameObjectSharedPtr go)
        {
            // if (go->descriptor_.name == "GameObject")
            // {
            //     go->descriptor_.name = ToString(go->descriptor_.type);
            // }

            auto config = Context::GetInstance().CurrentConfigure();
            auto root = std::filesystem::path(config.context_name);

            std::filesystem::path path;
            auto current = std::dynamic_pointer_cast<GameNode>(go);
            auto gn = current;
            while (current != nullptr && current->Parent().lock() != nullptr)
            {
                path = current->descriptor_.name / path;
                current = current->Parent().lock();
            }

            auto path_string = path.string();
            std::string illegal = ":\"\'<>%$*&+ ";
            for (auto c : illegal)
            {
                std::replace(path_string.begin(), path_string.end(), c, '_');
            }
            go->descriptor_.reference_path = root / path_string;

            // if (gn != nullptr)
            // {
            //     gn->ForEachChild<GameObject>([&](GameObjectSharedPtr node) { this->UpdateReferencePath(node); });
            // }
        }

        // std::filesystem::path ResourceManager::GetFilePath(const std::string file_name)
        // {
        //     for (const auto& file : std::filesystem::recursive_directory_iterator{this->resource_root_})
        //     {
        //         if(file.is_regular_file() && file.path().filename() == file_name)
        //         {
        //             return file.path();
        //         }
        //     }

        //     CHECK_AND_ASSERT(false, "Cannot find file/folder " << file_name);
        //     return nullptr;
        // }
        // void ResourceManager::DumpCurrentPath()
        // {
        //     PRINT("Current Root Path: " << this->resource_root_.string());
        // }

    }  // namespace Core

}  // namespace vEngine
