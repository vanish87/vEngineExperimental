#ifndef _VENGINE_RENDERING_DATA_CBUFFER_HPP
#define _VENGINE_RENDERING_DATA_CBUFFER_HPP

#pragma once

#if defined(VENGINE_HLSL)

#else

#include <engine.hpp>
#include <vengine/core/matrix.hpp>
using namespace vEngine::Math;

#endif

struct vEngineCameraConstantBuffer
{
	float4x4 view_matrix;
	float4x4 proj_matrix;
};

#endif /* _VENGINE_RENDERING_DATA_CBUFFER_HPP */
