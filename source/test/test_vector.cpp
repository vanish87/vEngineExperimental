
#include <gtest/gtest.h>

#include <vengine/core/predeclear.hpp>
#include <vengine/core/vector.hpp>

using namespace vEngine::Core;

TEST(Vector, IntAdd)
{
    int4 v0(1);
    int4 v1(2);

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


    // v4 += float4(2);
    // ASSERT_EQ(v4.x(), 9);
    // ASSERT_EQ(v4.y(), 9);
    // ASSERT_EQ(v4.z(), 9);
    // ASSERT_EQ(v4.w(), 9);

    // const int i = 10;
    // int4 v0(i);
    // ASSERT_EQ(v0.x(), 10);
    // ASSERT_EQ(v0.y(), 10);
    // ASSERT_EQ(v0.z(), 10);
    // int4 v1 = v0;

    // int4 v3;
    // v3 = v1;

    // int intarray[] = {0, 1, 2, 3};
    // int4 v4(intarray);

	// auto v5 = v3 + v4;
	
	// v5 += v1;

    // // Vector<int,2> v2;

    // // ASSERT_TRUE(v1.x());
    // ASSERT_EQ(v0.x(), v1.x());
    // ASSERT_EQ(v0.x(), 10);
}