


#include <gtest/gtest.h>

#include <engine.hpp>
#include <vengine/core/angle.hpp>

using namespace vEngine::Core;

TEST(Angle, Construct)
{
	// radian r = 3.14f; Error
	radian r(3.14f);
	degree d(90);

}