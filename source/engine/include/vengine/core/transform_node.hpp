/// \file transform_node.hpp
/// \brief Head file for Transform node
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_TRANSFORM_NODE_HPP
#define _VENGINE_CORE_TRANSFORM_NODE_HPP

#pragma once
#include "component_factory.hpp"
#include "engine.hpp"
#include "game_node.hpp"
#include "transform_component.hpp"

/// A brief namespace description.
namespace vEngine
{
    namespace Core
    {

        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class TransformNode : public GameNode
        {
            public:
                /// \brief brief constructor description.
                TransformNode(){};

                static TransformNodeSharedPtr Create()
                {
                    auto gn = std::make_shared<TransformNode>();
                    gn->transform_ = ComponentFactory::Create<TransformComponent>();
                    gn->AttachComponent(gn->transform_);
                    return gn;
                }

                TransformSharedPtr Transform()
                {
                    return this->transform_->game_object_;
                }

            public:
                TransformComponentSharedPtr transform_;
        };
    }  // namespace Core

}  // namespace vEngine

#endif /* _VENGINE_CORE_TRANSFORM_NODE_HPP */
