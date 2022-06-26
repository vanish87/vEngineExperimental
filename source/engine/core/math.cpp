#include <vengine/core/math.hpp>

namespace vEngine
{
    namespace Math
    {
        static const int FLOAT_MAX_ULP = 4;
        /// Use union to compare float
        bool CompareFloat(const float lhs, const float rhs)
        {
            union CompareUnion
            {
                    CompareUnion(float FIn = 1.0) : F(FIn){};

                    float F;
                    int64_t FInt;
            };
            CompareUnion LhsFloat(lhs);
            CompareUnion RhsFloat(rhs);

            // checking if NAN
            if (IsNAN(lhs) || IsNAN(rhs)) return false;
            if (IsINF(lhs) || IsINF(rhs)) return false;
            // checking sign
            if (std::signbit(lhs) != std::signbit(rhs))
            {
                // for +0.0 and -0.0 error
                if (lhs == rhs) return true;
                return false;
            }

            int64_t Ulps = std::abs(LhsFloat.FInt - RhsFloat.FInt);
            if (Ulps <= FLOAT_MAX_ULP) return true;
            return false;
        }

        // bool IsFloatEqual(float& lhs, float& rhs)
        // {
        //     return CompareFloat(lhs, rhs);
        // }

        bool IsFloatEqual(const float& lhs, const float& rhs)
        {
            return CompareFloat(lhs, rhs);
        }
        /// Another way to compare float with epsilon
        bool IsFloatEqual(const float& lhs, const float& rhs, const float epsilon)
        {
            auto e = Math::Abs(epsilon);
            // CHECK_ASSERT(epsilon != 0);
            return Math::Abs(lhs - rhs) < e;
        }
        float Abs(float num)
        {
            return std::fabs(num);
        }
        float Sqrt(float x)
        {
            CHECK_ASSERT(IsFloatEqual(x, 0) == false);
            return std::sqrt(x);
        }

        float Sin(float x)
        {
            return std::sin(x);
        }
        float Sin(radian x)
        {
            UNUSED_PARAMETER(x);
            return 0;
        }

        float Cos(float x)
        {
            return std::cos(x);
        }

        float ArcCos(float x)
        {
            return std::acos(x);
        }

        float Tan(float x)
        {
            return std::tan(x);
        }
        float ArcTan(float x)
        {
            return std::atan(x);
        }
        float Cot(float x)
        {
            return 1.0f / Tan(x);
        }

        float InvSqrt(float number)
        {
            if (IsFloatEqual(number, 0)) return 0;

            float xhalf = 0.5f * number;

            int i = *(int*)&number;     // get bits for floating value
            i = 0x5f3759df - (i >> 1);  // gives initial guess y0
            number = *(float*)&i;       // convert bits back to float
            // Newton step, repeating increases accuracy
            number = number * (1.5f - xhalf * number * number);
            // 2nd Newton step, repeating increases accuracy
            number = number * (1.5f - xhalf * number * number);
            return number;
        }

        float Ln(float x)
        {
            return std::log(x);
        }
        float Pow(float base, float exp)
        {
            return pow(base, exp);
        }
        color ToColor(const float4& float_color)
        {
            color ret;
            ret.x() = Math::CeilToInt<float, uint8_t>(float_color.x() * 255);
            ret.y() = Math::CeilToInt<float, uint8_t>(float_color.y() * 255);
            ret.z() = Math::CeilToInt<float, uint8_t>(float_color.z() * 255);
            ret.w() = Math::CeilToInt<float, uint8_t>(float_color.w() * 255);
            return ret;
        }
        float4 ToFloat(const color& color)
        {
            return float4(color) / float4(255, 255, 255, 255);
        }

    }  // namespace Math
}  // namespace vEngine
