
#include <gtest/gtest.h>

#include <engine.hpp>
#include <vengine/core/matrix.hpp>

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

    // auto m3 = float4x4(29);
    // m3 += float4x4(2);
    // ASSERT_TRUE(m3 == float4x4(31));

    // Matrix<float, 200, 300> matrixBig;

    // matrixBig[150][80] = 10;

    // ASSERT_FLOAT_EQ(matrixBig[150][80], 10);

    // Matrix<int, 200, 30> mb4(54);
    // for (size_t r = 0; r < mb4.row; ++r)
    // {
    //     for (size_t c = 0; c < mb4.col; ++c)
    //     {
    //         ASSERT_EQ(mb4[r][c], 54) << r << " " << c;
    //     }
    // }

    // m3 = m1 * m2;

    // Matrix<float, 200, 80> mb1(50);
    // Matrix<float, 50, 200> mb2(80);

    // auto mb3 = Multiply(mb1, mb2);

    // Matrix<int, 3, 2> m4;
    // Matrix<int, 2, 3> m5;

    // m4[0][0] = 4; m4[0][1] = 5; m4[0][2] = 7;
    // m4[1][0] = 2; m4[1][1] = 1; m4[1][2] = 0;

    // m5[0][0] = 2; m5[0][1] = 3;
    // m5[1][0] = 8; m5[1][1] = 9;
    // m5[2][0] = 1; m5[2][1] = 1;

    // auto m6 = Multiply(m4, m5);

    // ASSERT_EQ(m6[0][0], 55); ASSERT_EQ(m6[0][1], 64);
    // ASSERT_EQ(m6[1][0], 12); ASSERT_EQ(m6[1][1], 15);
}
