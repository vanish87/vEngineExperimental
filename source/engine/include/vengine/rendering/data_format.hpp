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
    }
}  // namespace vEngine

#endif /* _VENGINE_RENDERING_DATA_FORMAT_HPP */
