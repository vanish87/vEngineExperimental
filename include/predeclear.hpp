#ifndef _INCLUDE_PREDECLEAR_HPP
#define _INCLUDE_PREDECLEAR_HPP

#pragma once

#include <cstdint>
#include <memory>
namespace vEngine
{
#define CLASS_AND_SHARED_POINTER(name) \
    class name;                        \
    typedef std::shared_ptr<name> name##SharedPtr;

#define CLASS_AND_SHARED_WEAK_POINTER(name)        \
    class name;                                    \
    typedef std::shared_ptr<name> name##SharedPtr; \
    typedef std::weak_ptr<name> name##WeakPtr;

#define CLASS_AND_UNIQUE_POINTER(name) \
    class name;                        \
    typedef std::unique_ptr<name> name##UniquePtr;

#define STRUCT_AND_SHARED_POINTER(name) \
    struct name;                        \
    typedef std::shared_ptr<name> name##SharedPtr;

    template <typename T, std::size_t S>
    constexpr std::size_t array_length(const T (&)[S])
    {
        return S;
    }

    typedef std::int8_t int8_t;
    typedef std::int16_t int16_t;
    typedef std::int32_t int32_t;
    typedef std::int64_t int64_t;

    typedef unsigned char byte;
    typedef std::uint8_t uint8_t;
    typedef std::uint16_t uint16_t;
    typedef std::uint32_t uint32_t;
    typedef std::uint64_t uint64_t;
    namespace Core
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
        typedef Vector<uint8_t, 4> color;

        typedef Vector<double, 1> double1;
        typedef Vector<double, 2> double2;
        typedef Vector<double, 3> double3;
        typedef Vector<double, 4> double4;

        template <typename T>
        class Quaternion;

        typedef Quaternion<float> quaternion;

        template <typename T>
        class Radian;
        template <typename T>
        class Degree;

        typedef Radian<float> radian;
        typedef Degree<float> degree;

        template <typename T, int M, int N>
        class Matrix;

        typedef Matrix<float, 4, 4> float4x4;

        // class Window;
        // typedef std::shared_ptr<Window> vEngineWindowPtr;
        CLASS_AND_SHARED_POINTER(Window)
        class Application;

        CLASS_AND_SHARED_POINTER(GameObject)
        CLASS_AND_SHARED_POINTER(Camera)
        CLASS_AND_SHARED_POINTER(Light)
        CLASS_AND_SHARED_POINTER(Mesh)

        CLASS_AND_SHARED_WEAK_POINTER(GameNode)
        CLASS_AND_SHARED_POINTER(TransformNode)
        CLASS_AND_SHARED_POINTER(CameraComponent)
        CLASS_AND_SHARED_POINTER(LightComponent)
        CLASS_AND_SHARED_POINTER(MeshComponent)
        CLASS_AND_SHARED_POINTER(TransformComponent)
        // CLASS_AND_SHARED_POINTER(AssetComponent)

        CLASS_AND_SHARED_POINTER(Scene)

        CLASS_AND_SHARED_POINTER(IComponent)
        CLASS_AND_SHARED_POINTER(IRenderer)
        // CLASS_AND_SHARED_POINTER(IResource)
        // STRUCT_AND_SHARED_POINTER(ResourceDescriptor)

        CLASS_AND_SHARED_POINTER(ThreadJob)

        CLASS_AND_SHARED_POINTER(Transform)
    }  // namespace Core
    namespace Rendering
    {
        CLASS_AND_UNIQUE_POINTER(RenderEngine)
        CLASS_AND_SHARED_POINTER(PipelineState)
        CLASS_AND_SHARED_POINTER(FrameBuffer)
        CLASS_AND_SHARED_POINTER(GraphicsBuffer)
        CLASS_AND_SHARED_POINTER(Texture)
        CLASS_AND_SHARED_POINTER(MeshRendererComponent)

        CLASS_AND_SHARED_POINTER(Shader)
        CLASS_AND_SHARED_POINTER(Material)
    }  // namespace Rendering

    namespace Animation
    {
        CLASS_AND_SHARED_POINTER(Animator)
        CLASS_AND_SHARED_POINTER(AnimatorComponent)
        // CLASS_AND_SHARED_POINTER(Animation)
        CLASS_AND_SHARED_POINTER(AnimationClip)
        CLASS_AND_SHARED_POINTER(Bone)
        CLASS_AND_SHARED_POINTER(BoneComponent)
        CLASS_AND_SHARED_POINTER(Joint)
        // CLASS_AND_SHARED_POINTER(Skeleton)
        // CLASS_AND_SHARED_POINTER(SkeletonComponent)
        // CLASS_AND_SHARED_POINTER(JointComponent)
    }

#undef CLASS_AND_SHARED_POINTER
#undef CLASS_AND_UNIQUE_POINTER
#undef STRUCT_AND_SHARED_POINTER
}  // namespace vEngine

#endif /* _INCLUDE_PREDECLEAR_HPP */
