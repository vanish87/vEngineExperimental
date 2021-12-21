
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
	float4x4 m2(20);

	ASSERT_FALSE(m1 == m2);
	ASSERT_TRUE(m1 == float4x4(10));

	auto m3 = float4x4(29);
	m3 += float4x4(2);
	ASSERT_TRUE(m3 == float4x4(31));
}

