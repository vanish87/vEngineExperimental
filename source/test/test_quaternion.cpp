

#include <gtest/gtest.h>

#include <engine.hpp>
#include <vengine/core/quaternion.hpp>
#include <vengine/core/matrix.hpp>
#include <vengine/core/math.hpp>

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

	auto q4 = q3 * 2.0f;

	quaternion qx, py;
	auto r = NLerp(qx, py, 0.5f);

}