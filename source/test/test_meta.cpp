#include <gtest/gtest.h>

#include <engine.hpp>
#include <vengine/core/vector.hpp>
#include <vengine/core/matrix.hpp>
#include <vengine/data/meta.hpp>
#include <vengine/data/json.hpp>
#include <vengine/core/math.hpp>

using namespace vEngine::Core;

class Dog
{
        // template <typename Class, typename T>
        // friend struct Property;

        friend class JsonFunction;
        // friend struct Property;

        // std::string barkType;
        std::string color;
        int weight = 0;
        float num = 0.1f;

    public:
        float4x4 newWeight;

        PROPERTY(std::string, bark_type);

    public:
        Attribute<int> my_attribute_;
        Attribute<float4> my_float4_;
        Attribute<std::string> my_string_;
        // TexAttribute my_attribute_tex_;

        bool operator==(const Dog& rhs) const
        {
            return std::tie(_bark_type, color, weight) == std::tie(rhs._bark_type, rhs.color, rhs.weight);
        }

        constexpr static auto properties()
        {
            return std::make_tuple(
                // property(&Dog::newWeight, "newWeight"),
                // _barkType_pro,
                // property("barkType", &Dog::_bark_type, &Dog::Get_bark_type)
                property("barkType", &Dog::my_attribute_), property("tex", &Dog::my_string_), property("color", &Dog::color), property("weight", &Dog::weight), property("weightn32", &Dog::newWeight),
                property("myforlaot4", &Dog::my_float4_), property("flaot", &Dog::num));
            // property(&Dog::my_attribute_, "MyAttribute", ));
        };
};
class BadDog : public Dog
{
    public:
        Attribute<bool> bad_;

        constexpr static auto properties()
        {
            return std::tuple_cat(Dog::properties(), std::make_tuple(property("bad", &BadDog::bad_))

            );
            // property(&Dog::my_attribute_, "MyAttribute", ));
        };
};
TEST(Meta, Construct)
{
    // radian r = 3.14f; Error
    // auto d1 = Dog();
    // auto long_vector = Vector<float4, 128>();
    // nlohmann::json j;
    // ToJson(j, long_vector);
    // ToJson(j, d1);
    // auto d2 = Dog();
    // FromJson(j, d1);
    auto d1 = Dog();
    d1.my_string_.Set("New Value");
    d1.my_attribute_.Set(100);
    d1.my_float4_.Set(float4(1, 2, 3, 4));
    d1.newWeight = vEngine::Math::LookAtLH(float3::Zero(), float3::One(), float3(0, 1, 0));
    auto d3 = Dog();

    auto a = d3.my_attribute_.Get();
    d3.my_attribute_.Set(a);

    // auto name = d3.Getname();
    auto bark = d3.Get_bark_type();
    d3.Set_bark_type("Wang2");

    // nlohmann::json j;
    // ToJson(j, d1);

    // auto d4 = Dog();
    // FromJson(j, d4);

    // auto bd1 = BadDog();
    // bd1.bad_.Set(true);
    // bd1.my_string_.Set("Bad Dog");
    // ToJson(j, bd1);

    // auto bd2 = BadDog();
    // FromJson(j, bd2);
    // VE_INFO(j.dump());
    // auto json = JsonFunction::toJson(d1);
    // auto d2 = JsonFunction::fromJson<Dog>(json);
}