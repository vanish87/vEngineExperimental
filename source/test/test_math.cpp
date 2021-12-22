#include <gtest/gtest.h>
#include <vengine/core/math.h>

#include <vengine/core/matrix.hpp>
#include <vengine/core/predeclear.hpp>

using namespace vEngine::Math;

TEST(Math, Matrix)
{
    float a = 0;
    ASSERT_FALSE(IsNAN(a));

    ASSERT_FALSE(IsFloatEqual(2, 3));
    ASSERT_TRUE(IsFloatEqual(2, 2));

    float4x4 m1;
    float4x4 m2;

    auto m3 = Multiply(m1, m2);
}
