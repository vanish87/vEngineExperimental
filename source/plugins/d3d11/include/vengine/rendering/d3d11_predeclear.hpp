#ifndef _VENGINE_RENDERING_D3D11_PREDECLEAR_HPP
#define _VENGINE_RENDERING_D3D11_PREDECLEAR_HPP

#include <memory>

namespace vEngine
{
	#define CLASS_AND_SHARED_POINTER(name) \
    class name;                        \
    typedef std::shared_ptr<name> name##SharedPtr;

	#define CLASS_AND_UNIQUE_POINTER(name) \
    class name;                        \
    typedef std::unique_ptr<name> name##UniquePtr;

	#define STRUCT_AND_SHARED_POINTER(name) \
    struct name;                        \
    typedef std::shared_ptr<name> name##SharedPtr;

    namespace Rendering
    {
        CLASS_AND_SHARED_POINTER(D3D11FrameBuffer)
    }

	#undef CLASS_AND_SHARED_POINTER
	#undef CLASS_AND_UNIQUE_POINTER
	#undef STRUCT_AND_SHARED_POINTER
}  // namespace vEngine

#endif /* _VENGINE_RENDERING_D3D11_PREDECLEAR_HPP */
