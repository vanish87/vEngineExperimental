
#include <gtest/gtest.h>
#include <vector>

#include <engine.hpp>
#include <vengine/core/vector.hpp>

using namespace vEngine::Core;
using namespace vEngine::Math;

TEST(Vector, IntAdd)
{
    int4 v0(1);
    int4 v1(2);

    // int2 int2with4_parameter(1,2,3,4); //compile error

    auto v3 = v0 + v1;

    ASSERT_EQ(v3.x(), 3);
    ASSERT_EQ(v3.y(), 3);
    ASSERT_EQ(v3.z(), 3);
    ASSERT_EQ(v3.w(), 3);

    int4 v4(4);

    v4 += v3;
    ASSERT_EQ(v4.x(), 7);
    ASSERT_EQ(v4.y(), 7);
    ASSERT_EQ(v4.z(), 7);
    ASSERT_EQ(v4.w(), 7);

    // int4 v5 = {1, 2, 3};
}

TEST(Vector, IntCompare)
{
    ASSERT_TRUE(int4(2) == int4(2));
    ASSERT_TRUE(int4(2,5) == int4(2,5));
    ASSERT_FALSE(int4(3) == int4(2));
    ASSERT_FALSE(int4(2,3) == int4(2,4));

    ASSERT_TRUE(int4(1) == int4::One());
    ASSERT_TRUE(int4(0) == int4::Zero());

    auto zero = int4::Zero();
    ASSERT_EQ(zero.x(), 0);
    ASSERT_EQ(zero.y(), 0);
    ASSERT_EQ(zero.z(), 0);
    ASSERT_EQ(zero.w(), 0);

    auto one = int4::One();
    ASSERT_EQ(one.x(), 1);
    ASSERT_EQ(one.y(), 1);
    ASSERT_EQ(one.z(), 1);
    ASSERT_EQ(one.w(), 1);
}

TEST(Vector, IntSub)
{
    int4 v0(1);
    int4 v1(2);

    auto v3 = v0 - v1;

    ASSERT_EQ(v3.x(), -1);
    ASSERT_EQ(v3.y(), -1);
    ASSERT_EQ(v3.z(), -1);
    ASSERT_EQ(v3.w(), -1);

    int4 v4(4);

    v4 -= v3;
    ASSERT_EQ(v4.x(), 5);
    ASSERT_EQ(v4.y(), 5);
    ASSERT_EQ(v4.z(), 5);
    ASSERT_EQ(v4.w(), 5);


}
TEST(Vector, IntMul)
{
    int4 v0(2);
    int4 v1(20);

    auto v3 = v0 * v1;

    ASSERT_EQ(v3.x(), 40);
    ASSERT_EQ(v3.y(), 40);
    ASSERT_EQ(v3.z(), 40);
    ASSERT_EQ(v3.w(), 40);

    int4 v4(4);

    v4 *= v3;
    ASSERT_EQ(v4.x(), 160);
    ASSERT_EQ(v4.y(), 160);
    ASSERT_EQ(v4.z(), 160);
    ASSERT_EQ(v4.w(), 160);

    v4 = int4(2);

    v4 *= 20;
    ASSERT_TRUE(v4 == int4(40));
}
TEST(Vector, IntDiv)
{
    int4 v0(20);
    int4 v1(2);

    auto v3 = v0 / v1;

    ASSERT_EQ(v3.x(), 10);
    ASSERT_EQ(v3.y(), 10);
    ASSERT_EQ(v3.z(), 10);
    ASSERT_EQ(v3.w(), 10);

    int4 v4(40);

    v4 /= v3;
    ASSERT_EQ(v4.x(), 4);
    ASSERT_EQ(v4.y(), 4);
    ASSERT_EQ(v4.z(), 4);
    ASSERT_EQ(v4.w(), 4);

}
TEST(Vector, IntContainer)
{
    std::vector<int4> vec(10, int4(5));
    for(auto v : vec)
    {
        ASSERT_TRUE(v == int4(5));
    }
}

TEST(Vector, IntSwap)
{
    int4 v1 = int4(2);
    int4 v2 = int4(4);

    swap(v1, v2);

    ASSERT_TRUE(v1 == int4(4));
    ASSERT_TRUE(v2 == int4(2));

}

TEST(Vector, IntNegative)
{
    int4 v1 = int4(2);
    int4 v2 = -v1;


    ASSERT_TRUE(v1 == int4(2));
    ASSERT_TRUE(v2 == int4(-2));
}