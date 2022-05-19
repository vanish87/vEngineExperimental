
/// \file game_node_factory.cpp
/// \brief source file for Game Node Factory
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/core/game_node_factory.hpp>
#include <vengine/core/transform.hpp>
#include <vengine/core/transform_node.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Core
    {

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
        GameNodeSharedPtr GameNodeFactory::Create(const GameNodeDescription& desc)
        {
            switch (desc.type)
            {
                case GameNodeType::Transform:
                {
                    auto tgn = std::make_shared<TransformNode>();
                    ComponentDescription cdesc;
                    tgn->transform_ = Create<TransformComponent>(cdesc);
                    tgn->AttachComponent(tgn->transform_);
                    return tgn;
                }
                break;

                default:
                    break;
            }
            auto gn = std::make_shared<GameNode>();

            return gn;
        }

    }  // namespace Core
}  // namespace vEngine