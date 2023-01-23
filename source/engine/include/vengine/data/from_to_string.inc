namespace vEngine
{
    namespace Core
    {
        #define ENUM_CASE_TO_STRING(x) case x : return #x;
        #define STRING_TO_ENUM(x, str) if(#x == str) return x;

        template <std::size_t I, class T, typename S>
        auto CastByType(std::shared_ptr<S> ptr)
        {
            return std::dynamic_pointer_cast<std::tuple_element_t<I, T>>(ptr);
        }
        template <typename T>
        auto GetTypeString(std::shared_ptr<T> prt)
        {
            return typeid(T).name();
        }
        template <typename T, typename>
        std::string ToString(const T& obj)
        {
            return std::to_string(obj);
        }
        template <typename T, typename>
        const T FromString(const std::string& obj)
        {
            return std::stoi(obj);
        }
        template <typename T, typename>
        std::string ToString(const std::string& obj)
        {
            return obj;
        }
        template <typename T, typename>
        const std::string FromString(const std::string& obj)
        {
            return obj;
        }
        template <typename T, typename>
        std::string ToString(const Core::UUID& uuid)
        {
            return ToString(uuid.AsUint());
        }
        template <typename T, typename>
        const Core::UUID FromString(const std::string& obj)
        {
            return Core::UUID(std::stoi(obj));
        }
        template <typename T, typename>
        std::string ToString(const Rendering::ShaderType& obj)
        {
            switch (obj)
            {
                case Rendering::ShaderType::VS:
                    return "VS";
                case Rendering::ShaderType::GS:
                    return "GS";
                case Rendering::ShaderType::PS:
                    return "PS";
                case Rendering::ShaderType::CS:
                    return "CS";
                default:
                    break;
            }
            NOT_IMPL_ASSERT;
            return "NOT DEFINED";
        }
        template <typename T, typename>
        const Rendering::ShaderType FromString(const std::string& obj)
        {
            if (obj == "VS") return Rendering::ShaderType::VS;
            if (obj == "PS") return Rendering::ShaderType::PS;
            // case Rendering::ShaderType::GS: return "GS";
            // case Rendering::ShaderType::PS: return "PS";
            // case Rendering::ShaderType::CS: return "CS";
            NOT_IMPL_ASSERT;
            return Rendering::ShaderType::VS;
        }
        std::string ToString(const GameObjectType& obj)
        {
            switch (obj)
            {
                ENUM_CASE_TO_STRING(GameObjectType::GameObject);
                ENUM_CASE_TO_STRING(GameObjectType::GameNode);
                ENUM_CASE_TO_STRING(GameObjectType::Component);
                ENUM_CASE_TO_STRING(GameObjectType::Transform);
                ENUM_CASE_TO_STRING(GameObjectType::TransformComponent);
                ENUM_CASE_TO_STRING(GameObjectType::Camera);
                ENUM_CASE_TO_STRING(GameObjectType::CameraComponent);
                ENUM_CASE_TO_STRING(GameObjectType::Light);
                ENUM_CASE_TO_STRING(GameObjectType::LightComponent);
                ENUM_CASE_TO_STRING(GameObjectType::Mesh);
                ENUM_CASE_TO_STRING(GameObjectType::MeshComponent);
                ENUM_CASE_TO_STRING(GameObjectType::Scene);

                ENUM_CASE_TO_STRING(GameObjectType::Serializer);

                ENUM_CASE_TO_STRING(GameObjectType::Renderer);
                ENUM_CASE_TO_STRING(GameObjectType::RendererComponent);
                ENUM_CASE_TO_STRING(GameObjectType::MeshRenderer);
                ENUM_CASE_TO_STRING(GameObjectType::MeshRendererComponent);
                ENUM_CASE_TO_STRING(GameObjectType::Material);
                ENUM_CASE_TO_STRING(GameObjectType::Texture);
                ENUM_CASE_TO_STRING(GameObjectType::PipelineState);
                ENUM_CASE_TO_STRING(GameObjectType::Shader);

                ENUM_CASE_TO_STRING(GameObjectType::Bone);
                ENUM_CASE_TO_STRING(GameObjectType::BoneComponent);
                ENUM_CASE_TO_STRING(GameObjectType::Joint);
                ENUM_CASE_TO_STRING(GameObjectType::AnimationClip);
                ENUM_CASE_TO_STRING(GameObjectType::Animator);
                ENUM_CASE_TO_STRING(GameObjectType::AnimatorComponent);
                default:
                    break;
            }
            NOT_IMPL_ASSERT;
            return "NOT DEFINED";
        }
        template <typename T, typename>
        std::string ToString(const GameObjectType& obj)
        {
            return ToString(obj);
        }
        template <typename T, typename>
        const GameObjectType FromString(const std::string& str)
        {
            STRING_TO_ENUM(GameObjectType::GameObject, str);
            STRING_TO_ENUM(GameObjectType::GameNode, str);
            STRING_TO_ENUM(GameObjectType::Component, str);
            STRING_TO_ENUM(GameObjectType::Transform, str);
            STRING_TO_ENUM(GameObjectType::TransformComponent, str);
            STRING_TO_ENUM(GameObjectType::Camera, str);
            STRING_TO_ENUM(GameObjectType::CameraComponent, str);
            STRING_TO_ENUM(GameObjectType::Light, str);
            STRING_TO_ENUM(GameObjectType::LightComponent, str);
            STRING_TO_ENUM(GameObjectType::Mesh, str);
            STRING_TO_ENUM(GameObjectType::MeshComponent, str);
            STRING_TO_ENUM(GameObjectType::Scene, str);

            STRING_TO_ENUM(GameObjectType::Serializer, str);

            STRING_TO_ENUM(GameObjectType::Renderer, str);
            STRING_TO_ENUM(GameObjectType::RendererComponent, str);
            STRING_TO_ENUM(GameObjectType::MeshRenderer, str);
            STRING_TO_ENUM(GameObjectType::MeshRendererComponent, str);
            STRING_TO_ENUM(GameObjectType::Material, str);
            STRING_TO_ENUM(GameObjectType::Texture, str);
            STRING_TO_ENUM(GameObjectType::PipelineState, str);
            STRING_TO_ENUM(GameObjectType::Shader, str);

            STRING_TO_ENUM(GameObjectType::Bone, str);
            STRING_TO_ENUM(GameObjectType::BoneComponent, str);
            STRING_TO_ENUM(GameObjectType::Joint, str);
            STRING_TO_ENUM(GameObjectType::AnimationClip, str);
            STRING_TO_ENUM(GameObjectType::Animator, str);
            STRING_TO_ENUM(GameObjectType::AnimatorComponent, str);

            NOT_IMPL_ASSERT;
            return GameObjectType::GameObject;
        }
        // template <typename T, typename = std::enable_if_t<std::is_same<T, std::filesystem::path>::value, T>>
        // std::string ToString(const std::filesystem::path& obj)
        // {
        //     return obj.string();
        // }
        void SaveJson(const json& j, const std::filesystem::path& path)
        {
            auto folder = path.parent_path();
            if(!std::filesystem::exists(folder)) std::filesystem::create_directories(folder);

            std::ofstream outfile(path.string());
            outfile << std::setw(2) << j << std::endl;
            outfile.flush();
            outfile.close();
        }
        std::filesystem::path GameObjectToPath(const GameObjectDescriptor& desc)
        {
            auto config = Context::GetInstance().CurrentConfigure();
            auto path = config.resource_bin;
            auto context_name = config.context_name;
            // auto gn = std::dynamic_pointer_cast<GameNode>(go);
            // if(gn != nullptr)
            // {
            //     while(gn != nullptr)
            //     {
            //         path /= gn->descriptor_.name;
            //     }
            // }

            auto name = desc.name;
            auto type = ToString(desc.type);

            auto file_name = std::to_string(desc.uuid.AsUint()) + "_" + name + "_" + type + ".json";

            std::string illegal = ":\"\'<>%$*&+ ";
            for (auto c : illegal)
            {
                std::replace(file_name.begin(), file_name.end(), c, '_');
            }

            return path / context_name / file_name;
        }
        json LoadJson(const std::filesystem::path path)
        {
            std::ifstream file(path.string());
            auto j = json::parse(file);
            file.close();
            return j;
        }
    }  // namespace Core
}  // namespace vEngine