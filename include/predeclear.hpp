#ifndef _INCLUDE_PREDECLEAR_HPP
#define _INCLUDE_PREDECLEAR_HPP

#include <cstdint>
#include <memory>
namespace vEngine
{
    #define CLASS_AND_SHARED_POINTER(name) \
	class name;\
	typedef std::shared_ptr<name> name##SharedPtr;

    #define CLASS_AND_SHARED_WEAK_POINTER(name) \
	class name;\
	typedef std::shared_ptr<name> name##SharedPtr;\
	typedef std::weak_ptr<name> name##WeakPtr;

	#define CLASS_AND_UNIQUE_POINTER(name) \
	class name;\
	typedef std::unique_ptr<name> name##UniquePtr;

	#define STRUCT_AND_SHARED_POINTER(name) \
	struct name;\
	typedef std::shared_ptr<name> name##SharedPtr;

    typedef std::int8_t int8_t;
    typedef std::int16_t int16_t;
    typedef std::int32_t int32_t;
    typedef std::int64_t int64_t;

    typedef unsigned char byte;
    typedef std::uint8_t uint8_t;
    typedef std::uint16_t uint16_t;
    typedef std::uint32_t uint32_t;
    typedef std::uint64_t uint64_t;
    namespace Math
    {
        template <typename T, int N>
        class Vector;

        typedef Vector<int, 1> int1;
        typedef Vector<int, 2> int2;
        typedef Vector<int, 3> int3;
        typedef Vector<int, 4> int4;

        typedef Vector<float, 1> float1;
        typedef Vector<float, 2> float2;
        typedef Vector<float, 3> float3;
        typedef Vector<float, 4> float4;

        typedef Vector<double, 1> double1;
        typedef Vector<double, 2> double2;
        typedef Vector<double, 3> double3;
        typedef Vector<double, 4> double4;

        template <typename T, int M, int N>
        class Matrix;

        typedef Matrix<float, 4, 4> float4x4;
    }  // namespace Math
    namespace Core
    {
        class Window;
        typedef std::shared_ptr<Window> vEngineWindowPtr;
        class Application;

        CLASS_AND_SHARED_POINTER(GameObject)
        CLASS_AND_SHARED_POINTER(Material)
        CLASS_AND_SHARED_POINTER(Camera)
        CLASS_AND_SHARED_POINTER(Light)
        CLASS_AND_SHARED_POINTER(Mesh)

        CLASS_AND_SHARED_WEAK_POINTER(GameNode)
        CLASS_AND_SHARED_POINTER(CameraComponent)
        CLASS_AND_SHARED_POINTER(LightComponent)
        CLASS_AND_SHARED_POINTER(MeshComponent)
        CLASS_AND_SHARED_POINTER(TransformComponent)

        CLASS_AND_SHARED_POINTER(Scene)

        CLASS_AND_SHARED_POINTER(IComponent)
        CLASS_AND_SHARED_POINTER(IRenderer)
        CLASS_AND_SHARED_POINTER(IResource)

        CLASS_AND_SHARED_POINTER(ThreadJob)

        class Transform;
    }  // namespace Core
    namespace Rendering
    {
        CLASS_AND_UNIQUE_POINTER(RenderEngine)
        CLASS_AND_SHARED_POINTER(PipelineState)
        CLASS_AND_SHARED_POINTER(FrameBuffer)
        CLASS_AND_SHARED_POINTER(GraphicsBuffer)
        CLASS_AND_SHARED_POINTER(Texture)
        CLASS_AND_SHARED_POINTER(MeshRendererComponent)
        
        STRUCT_AND_SHARED_POINTER(Shader)
    }

	#undef CLASS_AND_SHARED_POINTER
	#undef CLASS_AND_UNIQUE_POINTER
	#undef STRUCT_AND_SHARED_POINTER
}  // namespace vEngine

#endif /* _INCLUDE_PREDECLEAR_HPP */
