
/// \file game_object.cpp
/// \brief source file for Game Object
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/game_object.hpp>
#include <vengine/core/game_node.hpp>
#include <vengine/core/context.hpp>
#include <vengine/data/from_to_string.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {
        const std::filesystem::path GameObjectDescriptor::AbsolutePath() const
        {
            auto config = Context::GetInstance().CurrentConfigure();
            return std::filesystem::absolute(config.resource_bin / this->reference_path);
        }

        const std::filesystem::path GameObjectDescriptor::ReferencePath() const
        {
            return this->reference_path;
        }
        const UUID GameObjectDescriptor::GetUUID() const
        {
            return this->uuid;
        }
        const std::filesystem::path GameObject::AbsolutePath() const
        {
            return this->descriptor_.AbsolutePath();
        }
        const std::filesystem::path GameObject::ReferencePath() const
        {
            return this->descriptor_.ReferencePath();
        }
        const std::filesystem::path GameObject::GetHierarchyPath() const
        {
            return std::filesystem::path();
        }
        void GameObject::UpdateReferencePath()
        {
            auto config = Context::GetInstance().CurrentConfigure();
            auto context_root = std::filesystem::path(config.context_name);

            auto desc = this->descriptor_;
            auto name = desc.name;
            std::string type;
            ToString(desc.type, type);
            auto file_name = std::to_string(desc.uuid.AsUint()) + "_" + name + "_" + type;
            auto file_ext = ".json";
            auto file_path = this->GetHierarchyPath();
            file_path = "";

            auto path_string = (context_root / file_path / file_name).string();
            const std::string illegal = ":\"\'<>%$*&+ .";
            for (const auto& c : illegal)
            {
                path_string.erase(std::remove(path_string.begin(), path_string.end(), c), path_string.end());
            }
            this->descriptor_.reference_path = path_string + file_ext;
        }
        GameObject::~GameObject() {}
    }  // namespace Core

}  // namespace vEngine