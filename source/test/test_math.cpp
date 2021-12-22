#include <gtest/gtest.h>

#include <vengine/core/predeclear.hpp>
#include <vengine/core/math.hpp>

using namespace vEngine::Math;

TEST(Math, Matrix)
{
	float a = 0;
	ASSERT_FALSE(IsNAN(a));
}
