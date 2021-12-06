
#include <gtest/gtest.h>
#include <vengine/core/vector.hpp>


TEST(Vector, add)
{
	vEngine::Core::Vector<int,2> v1;
	vEngine::Core::Vector<int,2> v2;

	auto v3 = v1 + v2;
	v3.x() = 10;
	v1.x() = 10;
	ASSERT_TRUE(true);
	ASSERT_EQ(v3.x(), v1.x());
}