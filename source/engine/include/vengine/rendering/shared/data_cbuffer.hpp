#ifndef _VENGINE_RENDERING_DATA_CBUFFER_HPP
#define _VENGINE_RENDERING_DATA_CBUFFER_HPP

#pragma once

#if defined(VENGINE_HLSL)

#define struct_def cbuffer
#define register_def(r) :register(r)

#else

#define struct_def struct
#define register_def(r) 

#include <engine.hpp>
#include <vengine/core/matrix.hpp>
using namespace vEngine::Math;

#endif

static const int vEngineConstantBufferPerCamera = 0;
static const int vEngineConstantBufferPerObject = 1;

struct_def vEngineCameraConstantBuffer register_def(b0)
{
	float4x4 view_matrix;
	float4x4 proj_matrix;
};
struct_def vEngineObjectConstantBuffer register_def(b1)
{
	float4x4 local_to_world_matrix;
};

#endif /* _VENGINE_RENDERING_DATA_CBUFFER_HPP */
