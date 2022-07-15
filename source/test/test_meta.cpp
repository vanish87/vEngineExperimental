#include <gtest/gtest.h>

#include <engine.hpp>
#include <vengine/core/vector.hpp>
#include <vengine/data/meta.hpp>

using namespace vEngine::Data;

TEST(Meta, Construct)
{
    // radian r = 3.14f; Error
    auto d1 = Dog();
    auto json = JsonFunction::toJson(d1);
    // auto d2 = JsonFunction::fromJson<Dog>(json);
}