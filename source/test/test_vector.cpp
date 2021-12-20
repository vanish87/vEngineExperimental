
#include <gtest/gtest.h>

#include <vengine/core/predeclear.hpp>
#include <vengine/core/vector.hpp>

using namespace vEngine::Core;

TEST(Vector, add)
{
	const int i = 10;
    int4 v0(i);
    ASSERT_EQ(v0.x(), 10);
    ASSERT_EQ(v0.y(), 10);
    ASSERT_EQ(v0.z(), 10);
    int4 v1 = v0;

    int4 v3;
    v3 = v1;

    int intarray[] = {0, 1, 2, 3};
    int4 v4(intarray);

	auto v5 = v3 + v4;
	
	v5 += v1;

    // Vector<int,2> v2;

    // ASSERT_TRUE(v1.x());
    ASSERT_EQ(v0.x(), v1.x());
    ASSERT_EQ(v0.x(), 10);
}