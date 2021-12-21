
#include <gtest/gtest.h>

#include <vengine/core/predeclear.hpp>
#include <vengine/core/matrix.hpp>

using namespace vEngine::Core;

TEST(Matrix, Init)
{
	float4x4 m0;

	float4x4 m1(m0);

	float4x4 m4 = m0;

	auto m3 = m0 + m1;





}
TEST(Matrix, Compare)
{
	float4x4 m1(10);
	float4x4 m2(10);

	ASSERT_TRUE(m1 == m2);
}

