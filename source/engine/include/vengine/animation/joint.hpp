/// \file example_class.hpp
/// \brief Head file for class dll.
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_ANIMATION_JOINT_HPP
#define _VENGINE_ANIMATION_JOINT_HPP

#pragma once

#include <engine.hpp>
#include <vengine/core/transform_node.hpp>
#include <vengine/core/matrix.hpp>

/// A brief namespace description.
namespace vEngine
{
    namespace Animation
    {
		using namespace Core;

		struct VertexWeight
		{
			uint32_t index;
			float weight;
		};
		
        /// \brief A brief class description.
        ///
        /// A detailed class description, it
        /// should be 2 lines at least.
        class Joint : public TransformNode
        {
            public:
                /// \brief brief constructor description.
                Joint();

                /// class variable description
                int public_variable_;


				std::vector<VertexWeight> weights;
				float4x4 inverse_bind_pos_matrix_;
            public:
                /// \brief A brief function description.
                ///
                /// \param p1 Description for p1.
                /// \param p2 Description for p2.
                /// \return Description for return value.
                int GetVariable(int p1, float p2);
        };
    }  // namespace Animation

}  // namespace vEngine

#endif /* _VENGINE_ANIMATION_JOINT_HPP */
