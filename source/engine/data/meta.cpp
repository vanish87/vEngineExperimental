/// \file meta.cpp
/// \brief source file for Meta
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#include <vengine/data/meta.hpp>

/// A detailed namespace description, it
/// should be 2 lines at least.
namespace vEngine
{
    namespace Data
    {

        /// constructor detailed defintion,
        /// should be 2 lines
        Meta::Meta() {}
        Meta::~Meta() {}

        /// A detailed function description, it
        /// should be 2 lines at least.
        int Meta::GetVariable(int p1, float p2)
        {
            UNUSED_PARAMETER(p1);
            UNUSED_PARAMETER(p2);
            return 1;
        }

    }  // namespace Data
}  // namespace vEngine

namespace Json
{
    template <>
    int& asAny<int>(Value& value)
    {
        return value.data.number;
    }

    template <>
    const int& asAny<int>(const Value& value)
    {
        return value.data.number;
    }
    template <>
    const std::string& asAny<std::string>(const Value& value)
    {
        return value.data.string;
    }

    template <>
    std::string& asAny<std::string>(Value& value)
    {
        return value.data.string;
    }
    template <>
    vEngine::Core::float4& asAny<vEngine::Core::float4>(Value& value)
    {
        return value.data.numberf;
    }
    template <>
    const vEngine::Data::Attribute<int>& asAny<vEngine::Data::Attribute<int>>(const Value& value)
    {
        return value.data.attri;
    }
    template <>
    const vEngine::Data::TexAttribute& asAny<vEngine::Data::TexAttribute>(const Value& value)
    {
        return value.data.tex;
    }

    template <>
    const vEngine::Core::float4& asAny<vEngine::Core::float4>(const Value& value)
    {
        return value.data.numberf;
    }
}  // namespace Json