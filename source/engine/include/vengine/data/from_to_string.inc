namespace vEngine
{
    namespace Core
    {
        #define ENUM_CASE_TO_STRING(x) case x : return #x;

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
                ENUM_CASE_TO_STRING(GameObjectType::Camera);
                ENUM_CASE_TO_STRING(GameObjectType::AnimationClip);
                ENUM_CASE_TO_STRING(GameObjectType::Texture);
                ENUM_CASE_TO_STRING(GameObjectType::Scene);
                default:
                    break;
            }
            // NOT_IMPL_ASSERT;
            return "NOT DEFINED";
        }
        template <typename T, typename>
        std::string ToString(const GameObjectType& obj)
        {
            return ToString(obj);
        }
        // template <typename T, typename = std::enable_if_t<std::is_same<T, std::filesystem::path>::value, T>>
        // std::string ToString(const std::filesystem::path& obj)
        // {
        //     return obj.string();
        // }
        void SaveJson(const json& j, const std::filesystem::path& path)
        {
            auto folder = path.parent_path();
            if(!std::filesystem::exists(folder)) std::filesystem::create_directory(folder);

            std::ofstream outfile(path.string());
            outfile << std::setw(2) << j << std::endl;
            outfile.flush();
            outfile.close();
        }
        std::filesystem::path GameObjectToPath(const GameObjectDescription& desc)
        {
            auto config = Context::GetInstance().CurrentConfigure();
            auto path = config.resource_bin;
            auto context_name = config.context_name;
            // auto gn = std::dynamic_pointer_cast<GameNode>(go);
            // if(gn != nullptr)
            // {
            //     while(gn != nullptr)
            //     {
            //         path /= gn->description_.name;
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