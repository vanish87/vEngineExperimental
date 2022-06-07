

#include <gtest/gtest.h>

#include <engine.hpp>
#include <vengine/core/quaternion.hpp>
#include <vengine/core/matrix.hpp>
#include <vengine/core/math.h>

using namespace vEngine::Core;
using namespace vEngine::Math;

TEST(Quaternion, Construct)
{
	quaternion q;
	q.x() = 1;
	q.y() = 2;

	quaternion q1;

	auto q3 = q * q1;

	auto con = q3.Conjugate();

	auto matrix = ToMatrix(q3);

}