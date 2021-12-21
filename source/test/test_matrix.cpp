
#include <gtest/gtest.h>

#include <vengine/core/predeclear.hpp>
#include <vengine/core/matrix.hpp>

using namespace vEngine::Core;

TEST(Matrix, Init)
{
	float4x4 m0;
	float4x4 m1;

	auto m3 = m0 + m1;
}
