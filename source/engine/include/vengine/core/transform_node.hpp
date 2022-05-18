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
                TransformNode()
				{
					this->transform_ = std::make_shared<TransformComponent>();
					this->AttachComponent(this->transform_);
				};

            public:
			 TransformComponentSharedPtr transform_;
        };
    }  // namespace Core

}  // namespace vEngine

#endif /* _VENGINE_CORE_TRANSFORM_NODE_HPP */
