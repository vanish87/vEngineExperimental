
#include <gtest/gtest.h>

#include <vengine/core/matrix.hpp>
#include <vengine/core/predeclear.hpp>
#include <vengine/core/debug.hpp>

using namespace vEngine::Core;
using namespace vEngine::Math;

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

    Matrix<float, 200, 300> matrixBig;

    matrixBig[150][80] = 10;

    ASSERT_FLOAT_EQ(matrixBig[150][80], 10);

    Matrix<int, 200, 30> mb4(54);
    for (size_t r = 0; r < mb4.row; ++r)
    {
        for (size_t c = 0; c < mb4.col; ++c)
        {
            ASSERT_EQ(mb4[r][c], 54) << r <<" " << c;
        }
    }

    m3 = m1 * m2;

    Matrix<float, 200, 80> mb1(50);
    Matrix<float, 50, 200> mb2(80);

    // Matrix<float, 5000, 2000> mb5(80);
    auto mb3 = Multiply(mb1, mb2);

    float4x4 rot;

    XRotation(rot, 2);
    YRotation(rot, 2);
    ZRotation(rot, 2);

    RotationAxis(rot, float3(1,2,3), 3.14f);

    float4x4 trans;
    Translate(trans, 2, 4, 5);
    Scale(trans, 20);
}
