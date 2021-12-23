#include <vengine/core/math.h>

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
            if ((std::signbit)(lhs) != (std::signbit)(rhs))
            {
                // for +0.0 and -0.0 error
                if (lhs == rhs) return true;
                return false;
            }

            int64_t Ulps = std::abs(LhsFloat.FInt - RhsFloat.FInt);
            if (Ulps <= FLOAT_MAX_ULP) return true;
            return false;
        }

        bool IsFloatEqual(float& lhs, float& rhs)
        {
            return CompareFloat(lhs, rhs);
        }

        bool IsFloatEqual(const float& lhs, const float& rhs)
        {
            return CompareFloat(lhs, rhs);
        }
        /// Another way to compare float with epsilon
        bool IsFloatEqual(float& lhs, float& rhs, const float epsilon)
        {
            auto e = Math::Abs(epsilon);
            // CHECK_ASSERT(epsilon != 0);
            return Math::Abs(lhs - rhs) < e;
        }
        /// Another way to compare float with epsilon
        bool IsFloatEqual(const float& lhs, const float& rhs,
                          const float epsilon)
        {
            auto e = Math::Abs(epsilon);
            // CHECK_ASSERT(epsilon != 0);
            return Math::Abs(lhs - rhs) < e;
        }
        float Abs(float num)
        {
            return std::fabs(num);
        }

    }  // namespace Math
}  // namespace vEngine
