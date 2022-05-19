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
#include "game_node_factory.hpp"
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


                TransformSharedPtr Transform()
                {
                    return this->transform_->GameObject();
                }
                
                virtual void AttachComponent(const GameNodeSharedPtr component) override;

            protected:
                TransformComponentSharedPtr transform_;
        };
    }  // namespace Core

}  // namespace vEngine

#endif /* _VENGINE_CORE_TRANSFORM_NODE_HPP */
