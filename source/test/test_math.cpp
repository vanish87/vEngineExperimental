#include <gtest/gtest.h>
#include <vengine/core/math.hpp>

#include <vengine/core/matrix.hpp>
#include <engine.hpp>

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

    UNUSED_PARAMETER(v3);
    UNUSED_PARAMETER(v4);

    auto v5 = Normalize(v1);
    UNUSED_PARAMETER(v5);

    float4x4 mpv = PerspectiveFovLH(0.5f, 1.2f, 2.0f, 200.0f);
    float4 point(3,1,2,1);

    // auto ndc = TransformPoint(point, mpv);
    // auto newndc = TransformVector(float4::Zero(), mpv);

    float4x4 identity;
    Identity(identity);

    auto transpose = Transpose(mpv);
    auto tb = Transpose(Matrix<float, 200, 300>());

    auto det = Determinant(mpv);
    det ++;

    auto outer = OuterProduct(v1, v2);
    UNUSED_PARAMETER(outer);

    auto outer1 = OuterProduct(Vector<float, 5>(), Vector<float, 10>());
    UNUSED_PARAMETER(outer1);

    auto view = LookAtLH(float3(0, 0, -10), float3(2, 3, 6), float3(0,1,0));
    UNUSED_PARAMETER(view);

    float4x4 rot;

    XRotation(rot, 2);
    YRotation(rot, 2);
    ZRotation(rot, 2);

    RotationAxis(rot, float3(1,2,3), 3.14f);

    float4x4 trans;
    Translate(trans, 2, 4, 5);
    Scale(trans, 20);

    auto inv = Inverse(mpv);
}
