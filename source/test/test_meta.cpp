#include <gtest/gtest.h>

#include <engine.hpp>
#include <vengine/core/vector.hpp>
#include <vengine/data/meta.hpp>
#include <vengine/data/json.hpp>

using namespace vEngine::Core;

TEST(Meta, Construct)
{
    // radian r = 3.14f; Error
    auto d1 = Dog();
    auto long_vector = Vector<float4, 128>();
    nlohmann::json j;
    ToJson(j, long_vector);
    auto json = JsonFunction::toJson(d1);
    // auto d2 = JsonFunction::fromJson<Dog>(json);
}