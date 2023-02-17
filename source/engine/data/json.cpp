/// \file json.inc
/// \brief source file for json
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/data/json.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {
        void SaveJson(const json& j, const std::filesystem::path path)
        {
            auto folder = path.parent_path();
            if (!std::filesystem::exists(folder)) std::filesystem::create_directories(folder);

            std::ofstream outfile(path.string());
            outfile << std::setw(2) << j << std::endl;
            outfile.flush();
            outfile.close();
        }
        const json LoadJson(const std::filesystem::path path)
        {
            std::ifstream file(path.string());
            auto j = json::parse(file);
            file.close();
            return j;
        }
        json ToJson(const std::vector<char>& vector)
        {
            return json(std::string(vector.begin(), vector.end()));
        }
        json ToJson(const std::filesystem::path& path)
        {
            return json(path.string());
        }
        json ToJson(const Rendering::ShaderType& shader_type)
        {
            std::string str;
            ToString(shader_type, str);
            return str;
        }
        json ToJson(const GameObjectType& go_type)
        {
            std::string str;
            ToString(go_type, str);
            return str;
        }
        void FromJson(const json& j, std::filesystem::path& path)
        {
            path = j.get<std::string>();
        }
        void FromJson(const json& j, GameObjectType& go_type)
        {
            FromString(j.get<std::string>(), go_type);
        }
        void FromJson(const json& j, Rendering::ShaderType& shader_type)
        {
            FromString(j.get<std::string>(), shader_type);
        }
        void FromJson(const json& j, std::vector<char>& vector)
        {
            vector.clear();
            auto data = j.get<std::string>();
            for (const auto& it : data)
            {
                vector.push_back(it);
            }
        }
    }  // namespace Core

}  // namespace vEngine