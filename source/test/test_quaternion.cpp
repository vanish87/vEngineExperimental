

#include <gtest/gtest.h>

#include <engine.hpp>
#include <vengine/core/quaternion.hpp>

using namespace vEngine::Core;

TEST(Quaternion, Construct)
{
	quaternion q;
	q.x() = 1;
	q.y() = 2;

}