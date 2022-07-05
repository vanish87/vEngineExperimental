#ifndef _VENGINE_RENDERING_DATA_FORMAT_HPP
#define _VENGINE_RENDERING_DATA_FORMAT_HPP

namespace vEngine
{
    namespace Rendering
    {
        enum class DataFormat
        {
            Undefined,
            RGBA32,

            RGFloat,
            RGBFloat,
            RGBAFloat,
            R32Int,
            RGBAInt,
            D24U8,
        };
        constexpr static uint8_t GetByteSize(const DataFormat f)
        {
            switch (f)
            {
            case DataFormat::RGBA32: return 4;
            case DataFormat::RGFloat: return 8;
            default:
                break;
            }

            return 0;
        }
    }
}  // namespace vEngine

#endif /* _VENGINE_RENDERING_DATA_FORMAT_HPP */
