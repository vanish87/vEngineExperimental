/// \file game_object_factory.cpp
/// \brief source file for Game Object Factory
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/game_object_factory.hpp>
#include <vengine/core/camera_component.hpp>
#include <vengine/core/transform_component.hpp>
#include <vengine/core/scene.hpp>

#include <vengine/data/class_bar.hpp>
#include <vengine/data/class_foo.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {

        GameObjectSharedPtr GameObjectFactory::CreateByTypeString(const std::string type)
        {

            PRINT_AND_BREAK("type " << type << " not created");
            NOT_IMPL_ASSERT;
            return nullptr;
        }
        /// A detailed function description, it
        /// should be 2 lines at least.
        // TransformNodeSharedPtr GameNodeFactory::Create()
        // {
        //     ComponentDescription desc;
        //     auto gn = std::make_shared<TransformNode>();
        //     gn->transform_ = Create<TransformComponent>(desc);
        //     gn->AttachComponent(gn->transform_);
        //     return gn;
        // }
        // Game GameNodeFactory::Create(const GameNodeDescription& desc)
        // {
        //     switch (desc.type)
        //     {
        //         case GameNodeType::Transform:
        //         {
        //             auto tgn = std::make_shared<TransformNode>();
        //             ComponentDescription cdesc;
        //             auto t = Create<TransformComponent>(cdesc);
        //             tgn->AttachComponent(t);
        //             return tgn;
        //         }
        //         break;

        //         default:
        //             break;
        //     }
        //     auto gn = std::make_shared<GameNode>();

        //     return gn;
        // }

    }  // namespace Core
}  // namespace vEngine