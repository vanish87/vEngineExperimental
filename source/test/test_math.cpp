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

    a = 2;
    float b = 2;
    ASSERT_TRUE(IsFloatEqual(a, b, 0.00001f));

    float4x4 m1;
    float4x4 m2;

    auto m3 = Multiply(m1, m2);


    float3 v1(1,2,3);
    float3 v2(4,5,6);

    auto v3 = Dot(v1, v2);
    auto v4 = Cross(v1, v2);

    auto v5 = Normalize(v1);

    float4x4 mpv = PerspectiveFovLH(0.5f, 1.2f, 2.0f, 200.0f);
    float4 point(3,1,2,1);

    auto ndc = TransformPoint(point, mpv);
    auto newndc = TransformVector(float4::Zero(), mpv);

    float4x4 identity;
    Identity(identity);

}
